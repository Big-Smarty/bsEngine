//
// Created by bigsmarty on 11/7/21.
//

#include "main.hpp"
#include "vk_engine.hpp"
#include "pipeline_builder.h"
#include "vk_initializers.hpp"

using namespace std;

void bsEngine::init_pipelines()
{

    VkShaderModule _fragmentModule;
    if (load_shader("../shaders/triangle.frag.spv", &_fragmentModule) != nullopt)
    {
        cout << "Successfully loaded the fragment shader module!\n";
    }
    else
    {
        cerr << "Failed to load the fragment shader module!\n";
        abort();
    }

    VkShaderModule _vertexModule;
    if (load_shader("../shaders/triangle.vert.spv", &_vertexModule) != nullopt)
    {
        cout << "Successfully loaded the vertex shader module!\n";
    }
    else
    {
        cerr << "Failed to load the vertex shader module!\n";
        abort();
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = vkinit::pipelineLayoutCreateInfo();

    VK_CHECK(vkCreatePipelineLayout(_logicalDevice, &pipelineLayoutInfo, nullptr, &_trianglePipelineLayout));

    PipelineBuilder pipelineBuilder;

    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, _vertexModule));
    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, _fragmentModule));

    VkPipelineColorBlendAttachmentState attachment = vkinit::createColorBlendAttachmentState();

    pipelineBuilder.shaderStageInfo = vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, _vertexModule);
    pipelineBuilder.vertexInputStateInfo = vkinit::vertexInputStateCreateInfo();
    pipelineBuilder.inputAssemblyStateInfo = vkinit::inputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    pipelineBuilder.tessellationStateInfo = vkinit::tessellationStateCreateInfo();

    pipelineBuilder.viewport.width = (float)_bs_window._windowExtent.width;
    pipelineBuilder.viewport.height = (float)_bs_window._windowExtent.height;
    pipelineBuilder.viewport.minDepth = 0.0f;
    pipelineBuilder.viewport.maxDepth = 1.0f;
    pipelineBuilder.scissor.offset = {0, 0};
    pipelineBuilder.scissor.extent = _bs_window._windowExtent;
    pipelineBuilder.viewport.x = 0;
    pipelineBuilder.viewport.y = 0;

    pipelineBuilder.viewportStateInfo = vkinit::viewportStateCreateInfo(&_viewport, &_scissor);
    pipelineBuilder.rasterizationStateInfo = vkinit::rasterizationStateCreateInfo();
    pipelineBuilder.multisampleStateInfo = vkinit::multisampleStateCreateInfoInfo();
    pipelineBuilder.depthStencilStateInfo = vkinit::depthStencilStateCreateInfo();
    pipelineBuilder.colorBlendInfo = vkinit::colorBlendStateCreateInfo(&attachment);
    pipelineBuilder.dynamicStateInfo = vkinit::dynamicStateCreateInfo();
    pipelineBuilder.pipelineLayout = _trianglePipelineLayout;

    _trianglePipeline = pipelineBuilder.build_pipeline(_logicalDevice, _renderPass);
    cout << "IT FUCKING WORKS\n";

}