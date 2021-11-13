//
// Created by bigsmarty on 11/12/21.
//

#pragma once

#include <main.h>
#include <vk_types.h>
//#include <vk_engine.h>
#include <glm/vec3.hpp>

struct VertexInputDescription
{

    std::vector<VkVertexInputBindingDescription> bindings;
    std::vector<VkVertexInputAttributeDescription> attributes;

    VkPipelineVertexInputStateCreateFlags  flags = 0;

};

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;

    static VertexInputDescription getVertexDescription();
};

struct Mesh
{
    std::vector<Vertex> _vertices;

    AllocatedBuffer _vertexBuffer;

    bool loadFromObj(const char* model);
};