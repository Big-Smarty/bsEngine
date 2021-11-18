//
// Created by bigsmarty on 11/5/21.
//

#include <main.h>
#include <base_engine/vk_engine.h>
#include <glm/gtx/transform.hpp>


void bsEngine::draw()
{

    VK_CHECK(vkWaitForFences(oVkEssentials._logicalDevice, 1, &getCurrentFrame()._renderFence, true, 1000000000));
    VK_CHECK(vkResetFences(oVkEssentials._logicalDevice, 1, &getCurrentFrame()._renderFence));

    uint32_t swapchainImageIndex;
    VK_CHECK(vkAcquireNextImageKHR(oVkEssentials._logicalDevice, oVkEssentials._swapchain, 1000000000, getCurrentFrame()._presentSemaphore, nullptr, &swapchainImageIndex));

    VK_CHECK(vkResetCommandBuffer(getCurrentFrame()._mainCommandBuffer, 0));

    VkCommandBuffer cmd = getCurrentFrame()._mainCommandBuffer;

    VkCommandBufferBeginInfo cmdBeginInfo = {

            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,
            .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo = nullptr,

    };

    VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));

    VkClearValue clearValue;
    float flash = abs(sin(frameNumber / 120.0f));
    clearValue.color =  {{flash, 0.0f, 10.0f, 0.0f}};

    VkClearValue depthClear;
    depthClear.depthStencil.depth = 1.0f;

    VkClearValue clearValues[] = {clearValue, depthClear};

    //start the main renderpass.
    //We will use the clear color from above, and the framebuffer of the index the swapchain gave us
    VkRenderPassBeginInfo rpInfo = {};
    rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpInfo.pNext = nullptr;

    rpInfo.renderPass = oVkEssentials._renderPass;
    rpInfo.renderArea.offset.x = 0;
    rpInfo.renderArea.offset.y = 0;
    rpInfo.renderArea.extent = oWindow._windowExtent;
    rpInfo.framebuffer = oVkEssentials._framebuffers[swapchainImageIndex];

    //connect clear values
    rpInfo.clearValueCount = 2;
    rpInfo.pClearValues = &clearValues[0];

    vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    draw_objects(cmd, renderables.data(), renderables.size());

    vkCmdEndRenderPass(cmd);
    VK_CHECK(vkEndCommandBuffer(cmd));

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submit = {

            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &getCurrentFrame()._presentSemaphore,
            .pWaitDstStageMask = &waitStage,
            .commandBufferCount = 1,
            .pCommandBuffers = &cmd,
            .signalSemaphoreCount = 1,
            .pSignalSemaphores = &getCurrentFrame()._renderSemaphore,

    };

    VK_CHECK(vkQueueSubmit(oVkEssentials._graphicsQueue, 1, &submit, getCurrentFrame()._renderFence));

    VkPresentInfoKHR presentInfo = {

            .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            .pNext = nullptr,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &getCurrentFrame()._renderSemaphore,
            .swapchainCount = 1,
            .pSwapchains = &oVkEssentials._swapchain,
            .pImageIndices = &swapchainImageIndex,
    };

    VK_CHECK(vkQueuePresentKHR(oVkEssentials._graphicsQueue, &presentInfo));

    frameNumber++;

    frametime = frametimeCounter();
}