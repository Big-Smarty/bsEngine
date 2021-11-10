//
// Created by bigsmarty on 11/9/21.
//

#pragma once
#include <main.hpp>
#include <vk_engine.hpp>

class PipelineBuilder {

public:
    VkPipeline build_pipeline(VkDevice device, VkRenderPass pass);


    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    VkPipelineShaderStageCreateInfo shaderStageInfo;
    VkPipelineVertexInputStateCreateInfo vertexInputStateInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo;
    VkPipelineTessellationStateCreateInfo tessellationStateInfo;
    VkPipelineViewportStateCreateInfo viewportStateInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationStateInfo;
    VkPipelineMultisampleStateCreateInfo multisampleStateInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineColorBlendAttachmentState colorBlendState;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout;
    VkViewport viewport;
    VkRect2D scissor;

};

