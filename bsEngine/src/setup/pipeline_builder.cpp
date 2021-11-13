//
// Created by bigsmarty on 11/9/21.
//

#include "pipeline_builder.h"

using namespace std;

VkPipeline PipelineBuilder::build_pipeline(VkDevice device, VkRenderPass pass)
{
    VkViewport _viewport;

    memset(&_viewport, 0xFF, sizeof(_viewport));

    _viewport = {

            .x = 0.0f,
            .y = 0.0f,
            .width = 1700.0f,
            .height = 900.0f,
            .minDepth = 0.0f,
            .maxDepth = 1.0f
    };

    VkRect2D _scissor;

    memset(&_scissor, 0xFF, sizeof(_scissor));

    _scissor = {

            .offset = {0, 0},
            .extent =  {1700, 900}
    };

    VkPipelineViewportStateCreateInfo _viewportState = {

            .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
            .pNext = nullptr,
            .viewportCount = 1,
            .pViewports = &_viewport,
            .scissorCount = 1,
            .pScissors = &_scissor,
    };

    VkGraphicsPipelineCreateInfo gpInfo = {

            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stageCount = static_cast<uint32_t>(shaderStages.size()),
            .pStages = shaderStages.data(),
            .pVertexInputState = &vertexInputStateInfo,
            .pInputAssemblyState = &inputAssemblyStateInfo,
            .pViewportState = &viewportStateInfo,
            .pRasterizationState = &rasterizationStateInfo,
            .pMultisampleState = &multisampleStateInfo,
            .pDepthStencilState = &depthStencilStateInfo,
            .pColorBlendState = &colorBlendInfo,
            .layout = pipelineLayout,
            .renderPass = pass,
            .subpass = 0,
            .basePipelineHandle = VK_NULL_HANDLE
    };

    VkPipeline newPipeline;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &gpInfo, nullptr, &newPipeline) != VK_SUCCESS)
    {

        cout << "Failed to create graphics pipeline!\n";
        return VK_NULL_HANDLE;
    }
    else
    {
        cout << "Successfully compiled graphics pipeline!\n";
        return newPipeline;
    }


}