//
// Created by bigsmarty on 11/9/21.
//

#include "pipeline_builder.h"

using namespace std;

VkPipeline PipelineBuilder::build_pipeline(VkDevice device, VkRenderPass pass)
{

    VkGraphicsPipelineCreateInfo gpInfo = {

            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .stageCount = static_cast<uint32_t>(shaderStages.size()),
            .pStages = shaderStages.data(),
            .pVertexInputState = &vertexInputStateInfo,
            .pInputAssemblyState = &inputAssemblyStateInfo,
            .pTessellationState = &tessellationStateInfo,
            .pViewportState = &viewportStateInfo,
            .pRasterizationState = &rasterizationStateInfo,
            .pMultisampleState = &multisampleStateInfo,
            .pDepthStencilState = &depthStencilStateInfo,
            .pColorBlendState = &colorBlendInfo,
            .pDynamicState = &dynamicStateInfo,
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

