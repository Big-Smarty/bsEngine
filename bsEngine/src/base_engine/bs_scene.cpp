//
// Created by bigsmarty on 11/12/21.
//

#include <main.h>
#include <base_engine/vk_engine.h>
#include <glm/gtx/transform.hpp>

void bsEngine::init_scene()
{

    RenderObject monke = {
            .mesh = get_mesh("monke"),
            .material = get_material("defaultmesh"),
            .transformMatrix = glm::translate(glm::mat4{ 1.0 }, glm::vec3(0, 0, 1))
    };

    _renderables.push_back(monke);

    for (int x = -10; x <= 10; x++) {
        for (int z = -20; z <= 0; z++) {

            glm::mat4 translation = glm::translate(glm::mat4{ 1.0 }, glm::vec3(x, 0, z));
            glm::mat4 scale = glm::scale(glm::mat4{ 1.0 }, glm::vec3(0.2, 0.2, 0.2));

            RenderObject tri = {
                    .mesh = get_mesh("monke"),
                    .material = get_material("defaultmesh"),
                    .transformMatrix = translation * scale
            };

            _renderables.push_back(tri);
        }
    }

}

void bsEngine::draw_objects(VkCommandBuffer cmd, RenderObject *first, int count) {

    inputValues.conRightX = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTX) / 32767;
    inputValues.conRightY = SDL_GameControllerGetAxis(controllerHandling.connectedControllers[0], SDL_CONTROLLER_AXIS_RIGHTY) / 32767;

    mouseInput.GetMouseDiff(inputValues.xOffset, inputValues.yOffset);

    camState.yaw += inputValues.xOffset + inputValues.conRightX;
    camState.pitch -= inputValues.yOffset + inputValues.conRightY;

    if(camState.pitch > 85.0f)
        camState.pitch = 85.0f;
    if(camState.pitch < -85.0f)
        camState.pitch = -85.0f;

    camState.direction.x = cos(glm::radians(camState.yaw)) * cos(glm::radians(camState.pitch));
    camState.direction.y = sin(glm::radians(camState.pitch));
    camState.direction.z = sin(glm::radians(camState.yaw)) * cos(glm::radians(camState.pitch));
    camState.cameraFront = glm::normalize(camState.direction);

    camState.camPos += camState.camMovement;

    camState.view = glm::lookAt(camState.camPos, camState.camPos + camState.cameraFront, camState.cameraUp);

    camState.projection = glm::perspective(glm::radians(70.0f), 1700.0f / 900.0f, 0.1f, 200.0f);
    camState.projection[1][1] *= -1;

    Mesh* lastMesh = nullptr;
    Material* lastMaterial = nullptr;

    for (int i = 0; i < count; i++)
    {

        RenderObject& object = first[i];

        //only bind pipeline if its different from already bound one
        if (object.material != lastMaterial)
        {
            vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, object.material->pipeline);
            lastMaterial = object.material;
        }

        glm::mat4 model;

        if (i == 0)
        {
            model = object.transformMatrix * glm::rotate(glm::mat4{ 1.0f }, glm::radians(_frameNumber * 1.5f), glm::vec3(0, 1, 0));

            glm::mat4 mesh_matrix = camState.projection * camState.view * model;

            MeshPushConstants constants = {
                    .render_matrix = mesh_matrix
            };

            vkCmdPushConstants(cmd, object.material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);

            //only bind the mesh if its different from the last one
            if (object.mesh != lastMesh)
            {
                VkDeviceSize offset = 0;
                vkCmdBindVertexBuffers(cmd, 0, 1, &object.mesh->_vertexBuffer._buffer, &offset);
                lastMesh = object.mesh;
            }

            vkCmdDraw(cmd, object.mesh->_vertices.size(), 1, 0, 0);
        }
        else
        {
            model = object.transformMatrix;

            glm::mat4 mesh_matrix = camState.projection * camState.view * model;

            MeshPushConstants constants = {
                    .render_matrix = mesh_matrix
            };

            vkCmdPushConstants(cmd, object.material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);

            //only bind the mesh if its different from the last one
            if (object.mesh != lastMesh)
            {
                VkDeviceSize offset = 0;
                vkCmdBindVertexBuffers(cmd, 0, 1, &object.mesh->_vertexBuffer._buffer, &offset);
                lastMesh = object.mesh;
            }

            vkCmdDraw(cmd, object.mesh->_vertices.size(), 1, 0, 0);
        }

    }

}