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

    renderables.push_back(monke);

    for (int x = -10; x <= 10; x++) {
        for (int z = -20; z <= 0; z++) {

            glm::mat4 translation = glm::translate(glm::mat4{ 1.0 }, glm::vec3(x, 0, z));
            glm::mat4 scale = glm::scale(glm::mat4{ 1.0 }, glm::vec3(0.2, 0.2, 0.2));

            RenderObject tri = {
                    .mesh = get_mesh("monke"),
                    .material = get_material("defaultmesh"),
                    .transformMatrix = translation * scale
            };

            renderables.push_back(tri);
        }
    }

}

void bsEngine::draw_objects(VkCommandBuffer cmd, RenderObject *first, int count) {

    Mesh* lastMesh = nullptr;
    Material* lastMaterial = nullptr;

    GPUCameraData gpuCameraData;
    gpuCameraData.proj = camState.projection;
    gpuCameraData.view = camState.view;
    gpuCameraData.viewproj = camState.projection * camState.view;

    void* data;
    vmaMapMemory(allocator, getCurrentFrame().cameraBuffer._allocation, &data);

    memcpy(data, &gpuCameraData, sizeof(GPUCameraData));

    vmaUnmapMemory(allocator, getCurrentFrame().cameraBuffer._allocation);

    for (int i = 0; i < count; i++)
    {

        RenderObject& object = first[i];

        //only bind pipeline if its different from already bound one
        if (object.material != lastMaterial)
        {
            vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, object.material->pipeline);
            lastMaterial = object.material;
            vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, object.material->pipelineLayout, 0, 1, &getCurrentFrame().globalDescriptor, 0, nullptr);
        }

        glm::mat4 model;

        model = object.transformMatrix;
        glm::mat4 mesh_matrix = camState.projection * camState.view * model;
        MeshPushConstants constants = {
                .render_matrix = object.transformMatrix
        };
        vkCmdPushConstants(cmd, object.material->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(MeshPushConstants), &constants);
        //only bind the mesh if its different from the last one
        if (object.mesh != lastMesh)
        {
            VkDeviceSize offset = 0;
            vkCmdBindVertexBuffers(cmd, 0, 1, &object.mesh->_vertexBuffer._buffer, &offset);
            //vkCmdBindIndexBuffer(cmd, object.mesh->_vertexBuffer._buffer, 0, VK_INDEX_TYPE_UINT32);
            lastMesh = object.mesh;
        }
        vkCmdDraw(cmd, object.mesh->_vertices.size(), 1, 0, 0);
        //vkCmdDrawIndexed(cmd, object.mesh->_vertices.size(), 401, 0, 0, 0);

    }

}