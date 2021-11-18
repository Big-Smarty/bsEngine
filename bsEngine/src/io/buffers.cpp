//
// Created by bigsmarty on 11/16/21.
//

#include "../main.h"
#include "../base_engine/vk_engine.h"
#include <vk_mem_alloc.h>

AllocatedBuffer bsEngine::createBuffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memUsage)
{
    VkBufferCreateInfo bufferInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .pNext = nullptr,
            .size = allocSize,
            .usage = usage,
    };

    VmaAllocationCreateInfo vmaAllocInfo = {
            .usage = memUsage
    };

    AllocatedBuffer newBuffer;
    VK_CHECK(vmaCreateBuffer(allocator, &bufferInfo, &vmaAllocInfo, &newBuffer._buffer, &newBuffer._allocation, nullptr));

    return newBuffer;
}