//
// Created by bigsmarty on 11/5/21.
//

#include <main.h>
#include <vk_engine.h>
#include <glm/gtx/transform.hpp>


void bsEngine::draw()
{

    VK_CHECK(vkWaitForFences(_logicalDevice, 1, &_renderFence, true, 1000000000));
    VK_CHECK(vkResetFences(_logicalDevice, 1, &_renderFence));

    uint32_t swapchainImageIndex;
    VK_CHECK(vkAcquireNextImageKHR(_logicalDevice, _swapchain, 1000000000, _presentSemaphore, nullptr, &swapchainImageIndex));

    VK_CHECK(vkResetCommandBuffer(_mainCommandBuffer, 0));

    VkCommandBuffer cmd = _mainCommandBuffer;

    VkCommandBufferBeginInfo cmdBeginInfo = {

            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .pNext = nullptr,
            .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
            .pInheritanceInfo = nullptr,

    };

    VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));

    VkClearValue clearValue;
    float flash = abs(sin(_frameNumber / 120.0f));
    clearValue.color =  {{flash, 0.0f, 10.0f, 0.0f}};

    VkClearValue depthClear;
    depthClear.depthStencil.depth = 1.0f;

    VkClearValue clearValues[] = {clearValue, depthClear};

    //start the main renderpass.
    //We will use the clear color from above, and the framebuffer of the index the swapchain gave us
    VkRenderPassBeginInfo rpInfo = {};
    rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpInfo.pNext = nullptr;

    rpInfo.renderPass = _renderPass;
    rpInfo.renderArea.offset.x = 0;
    rpInfo.renderArea.offset.y = 0;
    rpInfo.renderArea.extent = _bs_window._windowExtent;
    rpInfo.framebuffer = _framebuffers[swapchainImageIndex];

    //connect clear values
    rpInfo.clearValueCount = 2;
    rpInfo.pClearValues = &clearValues[0];

    vkCmdBeginRenderPass(cmd, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);

    draw_objects(cmd, _renderables.data(), _renderables.size());

    vkCmdEndRenderPass(cmd);
    VK_CHECK(vkEndCommandBuffer(cmd));

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submit = {

            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .pNext = nullptr,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &_presentSemaphore,
            .pWaitDstStageMask = &waitStage,
            .commandBufferCount = 1,
            .pCommandBuffers = &cmd,
            .signalSemaphoreCount = 1,
            .pSignalSemaphores = &_renderSemaphore,

    };

    VK_CHECK(vkQueueSubmit(_graphicsQueue, 1, &submit, _renderFence));

    VkPresentInfoKHR presentInfo = {

            .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
            .pNext = nullptr,
            .waitSemaphoreCount = 1,
            .pWaitSemaphores = &_renderSemaphore,
            .swapchainCount = 1,
            .pSwapchains = &_swapchain,
            .pImageIndices = &swapchainImageIndex,
    };

    VK_CHECK(vkQueuePresentKHR(_graphicsQueue, &presentInfo));

    _frameNumber++;

    _frametime = frametimeCounter();
}