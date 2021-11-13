//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <base_engine/vk_engine.h>

void bsEngine::init_commands()
{

    VkCommandPoolCreateInfo commandPoolInfo = vkinit::commandPoolCreateInfo(vkEssentials._graphicsQueueFamily,
                                                                            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    VK_CHECK(vkCreateCommandPool(vkEssentials._logicalDevice, &commandPoolInfo, nullptr, &vkEssentials._commandPool));

    VkCommandBufferAllocateInfo cmdAllocInfo = vkinit::commandBufferAllocateInfo(vkEssentials._commandPool, 1);
    VK_CHECK(vkAllocateCommandBuffers(vkEssentials._logicalDevice, &cmdAllocInfo, &vkEssentials._mainCommandBuffer));

    _mainDeletionQueue.push_function([=]()
                       {
                           vkDestroyCommandPool(vkEssentials._logicalDevice, vkEssentials._commandPool, nullptr);
                       });

}