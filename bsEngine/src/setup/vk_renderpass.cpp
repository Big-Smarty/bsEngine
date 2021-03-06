//
// Created by bigsmarty on 11/5/21.
//

#include <main.h>
#include <base_engine/vk_engine.h>

void bsEngine::init_default_renderpass()
{

    //the color attachment to use by the renderpass
    VkAttachmentDescription color_attachment = {

            .format = oVkEssentials._swapchainImageFormat, //the format required to be used in the swapchain
            .samples = VK_SAMPLE_COUNT_1_BIT, //no msaa
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, //clear the attachment when its loaded
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE, //store it when the renderpass ends
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, //no depth stencil yet
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, //no depth stencil yet
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, //the starting layout of the image doesnt really matter
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR //the final image of the layout should be optimal for displaying
    };

    VkAttachmentDescription depth_attachment = {

            .flags = 0,
            .format = depthFormat,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };

    VkAttachmentReference depth_attachment_ref = {

            .attachment = 1,
            .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };

    VkAttachmentReference color_attachment_ref = {

            .attachment = 0,
            .layout =VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    //create the minimum of one subpass
    VkSubpassDescription subpass = {

            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = 1,
            .pColorAttachments = &color_attachment_ref,
            .pDepthStencilAttachment = &depth_attachment_ref
    };

    VkAttachmentDescription attachments[2] = {color_attachment, depth_attachment};

    VkRenderPassCreateInfo render_pass_info = {

            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .pNext = nullptr,
            .attachmentCount = 2,
            .pAttachments = &attachments[0],
            .subpassCount = 1,
            .pSubpasses = &subpass
    };

    VK_CHECK(vkCreateRenderPass(oVkEssentials._logicalDevice, &render_pass_info, nullptr, &oVkEssentials._renderPass));

    mainDeletionQueue.push_function([=](){
        vkDestroyRenderPass(oVkEssentials._logicalDevice, oVkEssentials._renderPass, nullptr);
    });

}

void bsEngine::init_framebuffer()
{

    VkFramebufferCreateInfo fb_info = {

            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext = nullptr,
            .renderPass = oVkEssentials._renderPass,
            .attachmentCount = 1,
            .width = oWindow._windowExtent.width,
            .height = oWindow._windowExtent.height,
            .layers = 1
    };

    //grab the amount of images in the swapchain
    const uint32_t swapchain_imagecount = oVkEssentials._swapchainImages.size();
    oVkEssentials._framebuffers = std::vector<VkFramebuffer>(swapchain_imagecount);

    for (int i = 0; i < swapchain_imagecount; i++)
    {
        VkImageView attachments[2];
        attachments[0] = oVkEssentials._swapchainImageViews[i];
        attachments[1] = depthImageView;

        fb_info.attachmentCount = 2;
        fb_info.pAttachments = attachments;
        VK_CHECK(vkCreateFramebuffer(oVkEssentials._logicalDevice, &fb_info, nullptr, &oVkEssentials._framebuffers[i]));

        mainDeletionQueue.push_function([=]()
                                         {
                                             vkDestroyFramebuffer(oVkEssentials._logicalDevice, oVkEssentials._framebuffers[i], nullptr);
                                             vkDestroyImageView(oVkEssentials._logicalDevice, oVkEssentials._swapchainImageViews[i], nullptr);
                                         });
    };

}