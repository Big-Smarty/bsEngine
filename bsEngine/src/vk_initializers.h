// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <main.h>
#include <vulkan/vulkan_core.h>

namespace vkinit {

    VkRenderPassBeginInfo renderPassBeginInfo(VkRenderPass pass, VkExtent2D extent, VkFramebuffer frameBuffer);

    VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

    VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t count = 1, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    VkShaderModuleCreateInfo createShaderInfo(size_t shaderSize, const uint32_t* shaderCode);

    VkPipelineShaderStageCreateInfo shaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule);

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo();

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo(VkPrimitiveTopology topology);

    VkPipelineTessellationStateCreateInfo tessellationStateCreateInfo();

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo(VkViewport* viewport, VkRect2D* scissor);

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo();

    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfoInfo();

    VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo(bool bDepthTest, bool bDepthWrite, VkCompareOp compareOp);

    VkPipelineColorBlendAttachmentState createColorBlendAttachmentState();

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* attachment);

    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo();

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo();

    VkImageCreateInfo imageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);
    VkImageViewCreateInfo imageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);

}

