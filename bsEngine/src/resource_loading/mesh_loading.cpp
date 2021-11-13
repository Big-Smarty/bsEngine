//
// Created by bigsmarty on 11/12/21.
//

#include "base_engine/vk_engine.h"
#include "main.h"

void bsEngine::load_meshes()
{

    //load the green triangle
    //make the array 3 vertices long
    _triangleMesh._vertices.resize(3);

    //vertex positions
    _triangleMesh._vertices[0].position = { 1.f, 1.f, 0.0f };
    _triangleMesh._vertices[1].position = {-1.f, 1.f, 0.0f };
    _triangleMesh._vertices[2].position = { 0.f,-1.f, 0.0f };

    //vertex colors, all green
    _triangleMesh._vertices[0].color = { 0.f, 1.f, 0.0f }; //pure green
    _triangleMesh._vertices[1].color = { 0.f, 1.f, 0.0f }; //pure green
    _triangleMesh._vertices[2].color = { 0.f, 1.f, 0.0f }; //pure green

    //we don't care about the vertex normals

    _monkeyMesh.loadFromObj("../assets/monkey_smooth.obj");
    //_waifuMesh.loadFromObj("../assets/fireyaretziresp.obj");

    upload_mesh(_triangleMesh);
    upload_mesh(_monkeyMesh);
    //upload_mesh(_waifuMesh);

    //MONKE
    _meshes["monke"] = _monkeyMesh;
    _meshes["triangle"] = _triangleMesh;
}


void bsEngine::upload_mesh(Mesh& mesh)
{
    //allocate vertex buffer
    VkBufferCreateInfo bufferInfo = {};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    //this is the total size, in bytes, of the buffer we are allocating
    bufferInfo.size = mesh._vertices.size() * sizeof(Vertex);
    //this buffer is going to be used as a Vertex Buffer
    bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;


    //let the VMA library know that this data should be writeable by CPU, but also readable by GPU
    VmaAllocationCreateInfo vmaallocInfo = {};
    vmaallocInfo.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;

    //allocate the buffer
    VK_CHECK(vmaCreateBuffer(_allocator, &bufferInfo, &vmaallocInfo,
                             &mesh._vertexBuffer._buffer,
                             &mesh._vertexBuffer._allocation,
                             nullptr));

    //add the destruction of triangle mesh buffer to the deletion queue
    _mainDeletionQueue.push_function([=]() {

        vmaDestroyBuffer(_allocator, mesh._vertexBuffer._buffer, mesh._vertexBuffer._allocation);
    });

    //copy vertex data
    void* data;
    vmaMapMemory(_allocator, mesh._vertexBuffer._allocation, &data);

    memcpy(data, mesh._vertices.data(), mesh._vertices.size() * sizeof(Vertex));

    vmaUnmapMemory(_allocator, mesh._vertexBuffer._allocation);
}
