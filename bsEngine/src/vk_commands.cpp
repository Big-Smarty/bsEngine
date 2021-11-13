//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <vk_engine.h>

void bsEngine::init_commands()
{

    VkCommandPoolCreateInfo commandPoolInfo = vkinit::commandPoolCreateInfo(_graphicsQueueFamily,
                                                                            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    VK_CHECK(vkCreateCommandPool(_logicalDevice, &commandPoolInfo, nullptr, &_commandPool));

    VkCommandBufferAllocateInfo cmdAllocInfo = vkinit::commandBufferAllocateInfo(_commandPool, 1);
    VK_CHECK(vkAllocateCommandBuffers(_logicalDevice, &cmdAllocInfo, &_mainCommandBuffer));

    _mainDeletionQueue.push_function([=]()
                       {
                           vkDestroyCommandPool(_logicalDevice, _commandPool, nullptr);
                       });

}