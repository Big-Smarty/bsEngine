//
// Created by bigsmarty on 11/12/21.
//

#include "vk_mesh.h"
#include <tiny_obj_loader.h>
#include <iostream>

using namespace std;

VertexInputDescription Vertex::getVertexDescription()
{
    VertexInputDescription description;

    //we will have just 1 vertex buffer binding, with a per-vertex rate
    VkVertexInputBindingDescription mainBinding = {
            .binding = 0,
            .stride = sizeof(Vertex),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
    };

    description.bindings.push_back(mainBinding);

    //Position will be stored at Location 0
    VkVertexInputAttributeDescription positionAttribute = {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(Vertex, position),
    };

    //Normal will be stored at Location 1
    VkVertexInputAttributeDescription normalAttribute = {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(Vertex, normal),
    };

    //Color will be stored at Location 2
    VkVertexInputAttributeDescription colorAttribute = {
            .location = 2,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(Vertex, color),
    };

    description.attributes.push_back(positionAttribute);
    description.attributes.push_back(normalAttribute);
    description.attributes.push_back(colorAttribute);
    return description;
}

bool Mesh::loadFromObj(const char* model)
{

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;



    std::string warn;
    std::string err;

    tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, model, "../assets/");

    if(!warn.empty())
    {
        cout << "WARNING: " << warn << endl;
    }

    if (!err.empty())
    {
        cerr << "ERROR: " << err << endl;
        return false;
    }

    for (auto & shape : shapes)
    {

        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {

            int fv = 3;

            for (size_t v = 0; v < fv; v++)
            {

                //access to vertex
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                //vertex position
                tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
                tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
                tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

                //vertex normal
                tinyobj::real_t nx = attrib.vertices[3 * idx.normal_index + 0];
                tinyobj::real_t ny = attrib.vertices[3 * idx.normal_index + 1];
                tinyobj::real_t nz = attrib.vertices[3 * idx.normal_index + 2];

                //copy everything into the vertex
                Vertex new_vert = {
                        .position.x = vx,
                        .position.y = vy,
                        .position.z = vz,

                        .normal.x = nx,
                        .normal.y = ny,
                        .normal.z = nz,

                        .color = new_vert.normal
                };

                _vertices.push_back(new_vert);

            }

            index_offset += fv;

        }

    }
    return true;

}