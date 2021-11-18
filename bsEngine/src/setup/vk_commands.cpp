//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <base_engine/vk_engine.h>

void bsEngine::init_commands()
{

    VkCommandPoolCreateInfo commandPoolInfo = vkinit::commandPoolCreateInfo(oVkEssentials._graphicsQueueFamily,
                                                                            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    for (int i = 0; i < FRAME_OVERLAP; i++)
    {
        VK_CHECK(vkCreateCommandPool(oVkEssentials._logicalDevice, &commandPoolInfo, nullptr, &oFrameData[i]._commandPool));

        VkCommandBufferAllocateInfo cmdAllocInfo = vkinit::commandBufferAllocateInfo(oFrameData[i]._commandPool, 1);
        VK_CHECK(vkAllocateCommandBuffers(oVkEssentials._logicalDevice, &cmdAllocInfo, &oFrameData[i]._mainCommandBuffer));

        mainDeletionQueue.push_function([=]()
                                         {
                                             vkDestroyCommandPool(oVkEssentials._logicalDevice, oFrameData[i]._commandPool, nullptr);
                                         });
    }

}