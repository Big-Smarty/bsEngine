#include <setup/vk_initializers.h>

VkRenderPassBeginInfo vkinit::renderPassBeginInfo(VkRenderPass pass, VkExtent2D extent, VkFramebuffer frameBuffer){

    VkRenderPassBeginInfo rpInfo = {};
    rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpInfo.pNext = nullptr;

    rpInfo.renderPass = pass;
    rpInfo.renderArea.offset.x = 0;
    rpInfo.renderArea.offset.y = 0;
    rpInfo.renderArea.extent = extent;
    rpInfo.framebuffer = frameBuffer;

    return rpInfo;

}

VkCommandPoolCreateInfo vkinit::commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags)
{

    VkCommandPoolCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .pNext = nullptr,
            .flags = flags,
            .queueFamilyIndex = queueFamilyIndex

    };

    return info;

}

VkCommandBufferAllocateInfo vkinit::commandBufferAllocateInfo(VkCommandPool pool, uint32_t count, VkCommandBufferLevel level)
{

    VkCommandBufferAllocateInfo info = {

            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .pNext = nullptr,
            .commandPool = pool,
            .level = level,
            .commandBufferCount = count

    };

    return info;
}

VkShaderModuleCreateInfo vkinit::createShaderInfo(size_t shaderSize, const uint32_t* shaderCode)
{

    VkShaderModuleCreateInfo shaderInfo = {

            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .codeSize = shaderSize,
            .pCode = shaderCode
    };

    return shaderInfo;
}

VkPipelineShaderStageCreateInfo vkinit::shaderStageCreateInfo(VkShaderStageFlagBits stage,VkShaderModule shaderModule)
{

    VkPipelineShaderStageCreateInfo stageInfo = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .pNext = nullptr,
            .stage = stage,
            .module = shaderModule,
            .pName = "main"
    };

    return stageInfo;
}

VkPipelineVertexInputStateCreateInfo vkinit::vertexInputStateCreateInfo()
{

    VkPipelineVertexInputStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .vertexBindingDescriptionCount = 0,
            .vertexAttributeDescriptionCount = 0
    };

    return info;
}

VkPipelineInputAssemblyStateCreateInfo vkinit::inputAssemblyStateCreateInfo(VkPrimitiveTopology topology)
{

    VkPipelineInputAssemblyStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .topology = topology,
            .primitiveRestartEnable = VK_FALSE
    };

    return info;

}

VkPipelineTessellationStateCreateInfo vkinit::tessellationStateCreateInfo()
{

    VkPipelineTessellationStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .patchControlPoints = 0
    };

    return info;

}

VkPipelineViewportStateCreateInfo vkinit::viewportStateCreateInfo(VkViewport* viewport, VkRect2D* scissor)
{

    VkPipelineViewportStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .viewportCount = 1,
            .pViewports = viewport,
            .scissorCount = 1,
            .pScissors = scissor
    };

    return info;

}

VkPipelineRasterizationStateCreateInfo vkinit::rasterizationStateCreateInfo()
{

    VkPipelineRasterizationStateCreateInfo info{

        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f
    };

    return info;

}

VkPipelineMultisampleStateCreateInfo vkinit::multisampleStateCreateInfoInfo()
{

    VkPipelineMultisampleStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
            .sampleShadingEnable = VK_FALSE,
            .minSampleShading = 1.0f,
            .pSampleMask = nullptr,
            .alphaToCoverageEnable = VK_FALSE,
            .alphaToOneEnable = VK_FALSE
    };

    return info;

}

VkPipelineDepthStencilStateCreateInfo vkinit::depthStencilStateCreateInfo(bool bDepthTest, bool bDepthWrite, VkCompareOp compareOp)
{

    VkPipelineDepthStencilStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .depthTestEnable = bDepthTest ? VK_TRUE : VK_FALSE,
            .depthWriteEnable = bDepthWrite ? VK_TRUE : VK_FALSE,
            .depthCompareOp = bDepthTest ? compareOp : VK_COMPARE_OP_ALWAYS,
            .depthBoundsTestEnable = VK_FALSE,
            .stencilTestEnable = VK_FALSE,
            .minDepthBounds = 0.0f,
            .maxDepthBounds = 1.0f
    };

    return info;

}

VkPipelineColorBlendAttachmentState vkinit::createColorBlendAttachmentState()
{

    VkPipelineColorBlendAttachmentState state = {

            .blendEnable = VK_FALSE,
            .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    };

    return state;

}

VkPipelineColorBlendStateCreateInfo vkinit::colorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* attachment)
{

    VkPipelineColorBlendStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .logicOpEnable = VK_FALSE,
            .logicOp = VK_LOGIC_OP_COPY,
            .attachmentCount = 1,
            .pAttachments = attachment,
            .blendConstants = {50.0, 50.0, 50.0, 1.0}
    };

    return info;

}

VkPipelineDynamicStateCreateInfo vkinit::dynamicStateCreateInfo()
{

    VkPipelineDynamicStateCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .dynamicStateCount = 0,
            .pDynamicStates = nullptr
    };

    return info;
}

VkPipelineLayoutCreateInfo vkinit::pipelineLayoutCreateInfo()
{

    VkPipelineLayoutCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .setLayoutCount = 0,
            .pSetLayouts = nullptr,
            .pushConstantRangeCount = 0,
            .pPushConstantRanges = nullptr
    };

    return info;

}

VkImageCreateInfo vkinit::imageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent)
{

    VkImageCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .pNext = nullptr,
            .imageType = VK_IMAGE_TYPE_2D,
            .format = format,
            .extent = extent,
            .mipLevels = 1,
            .arrayLayers = 1,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .tiling = VK_IMAGE_TILING_OPTIMAL,
            .usage = usageFlags
    };

    return info;

}

VkImageViewCreateInfo vkinit::imageViewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags)
{

    VkImageViewCreateInfo info = {

            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = nullptr,
            .image = image,
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = format,
            .subresourceRange = {
                    .aspectMask = aspectFlags,
                    .baseMipLevel = 0,
                    .levelCount = 1,
                    .baseArrayLayer = 0,
                    .layerCount = 1,
            }
    };

    return info;

}
