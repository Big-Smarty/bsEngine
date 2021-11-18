//
// Created by bigsmarty on 11/12/21.
//

#include "base_engine/vk_engine.h"
#include "main.h"

void bsEngine::load_meshes()
{

    //we don't care about the vertex normals

    monkeyMesh.loadFromObj("../assets/monkey_smooth.obj");

    upload_mesh(monkeyMesh);

    //MONKE
    meshes["monke"] = monkeyMesh;

}


void bsEngine::upload_mesh(Mesh& mesh)
{
    //allocate vertex buffer
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    //this is the total size, in bytes, of the buffer we are allocating
    bufferInfo.size = mesh._vertices.size() * sizeof(Vertex);
    //this buffer is going to be used as a Vertex Buffer
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;


    //let the VMA library know that this data should be writeable by CPU, but also readable by GPU
    VmaAllocationCreateInfo vmaallocInfo = {};
    vmaallocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    //allocate the buffer
    VK_CHECK(vmaCreateBuffer(allocator, &bufferInfo, &vmaallocInfo,
                             &mesh._vertexBuffer._buffer,
                             &mesh._vertexBuffer._allocation,
                             nullptr));

    //add the destruction of triangle mesh buffer to the deletion queue
    mainDeletionQueue.push_function([=]() {

        vmaDestroyBuffer(allocator, mesh._vertexBuffer._buffer, mesh._vertexBuffer._allocation);
    });

    //copy vertex data
    void* data;
    vmaMapMemory(allocator, mesh._vertexBuffer._allocation, &data);

    memcpy(data, mesh._vertices.data(), mesh._vertices.size() * sizeof(Vertex));

    vmaUnmapMemory(allocator, mesh._vertexBuffer._allocation);
}
