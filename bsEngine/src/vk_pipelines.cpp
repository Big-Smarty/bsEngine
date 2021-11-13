//
// Created by bigsmarty on 11/7/21.
//

#include "main.h"
#include "vk_engine.h"
#include "pipeline_builder.h"
#include "vk_initializers.h"

using namespace std;

void bsEngine::init_pipelines() {

    VkPipelineLayoutCreateInfo meshPipelineLayoutInfo = vkinit::pipelineLayoutCreateInfo();

    VkPushConstantRange pushConstant = {
            .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
            .offset = 0,
            .size = sizeof(MeshPushConstants),
    };

    meshPipelineLayoutInfo.pushConstantRangeCount = 1;
    meshPipelineLayoutInfo.pPushConstantRanges = &pushConstant;

    VK_CHECK(vkCreatePipelineLayout(_logicalDevice, &meshPipelineLayoutInfo, nullptr, &_meshPipelineLayout));

    VkShaderModule RGBfragmentModule;
    if (load_shader("../shaders/rgb_triangle.frag.spv", &RGBfragmentModule) != nullopt) {
        cout << "Successfully loaded the fragment shader module!\n";
    } else {
        cerr << "Failed to load the fragment shader module!\n";
        abort();
    }

    VkShaderModule RGBvertexModule;
    if (load_shader("../shaders/rgb_triangle.vert.spv", &RGBvertexModule) != nullopt) {
        cout << "Successfully loaded the vertex shader module!\n";
    } else {
        cerr << "Failed to load the vertex shader module!\n";
        abort();
    }

    VkShaderModule _redfragmentModule;
    if (load_shader("../shaders/triangle.frag.spv", &_redfragmentModule) != nullopt) {
        cout << "Successfully loaded the fragment shader module!\n";
    } else {
        cerr << "Failed to load the fragment shader module!\n";
        abort();
    }

    VkShaderModule _redvertexModule;
    if (load_shader("../shaders/triangle.vert.spv", &_redvertexModule) != nullopt) {
        cout << "Successfully loaded the vertex shader module!\n";
    } else {
        cerr << "Failed to load the vertex shader module!\n";
        abort();
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = vkinit::pipelineLayoutCreateInfo();

    VK_CHECK(vkCreatePipelineLayout(_logicalDevice, &pipelineLayoutInfo, nullptr, &genericPipelineLayout));

    PipelineBuilder pipelineBuilder;

    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, _redvertexModule));
    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, _redfragmentModule));

    VkPipelineColorBlendAttachmentState attachment = vkinit::createColorBlendAttachmentState();

    pipelineBuilder.vertexInputStateInfo = vkinit::vertexInputStateCreateInfo();
    pipelineBuilder.inputAssemblyStateInfo = vkinit::inputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    pipelineBuilder.viewport.x = 0.0f;
    pipelineBuilder.viewport.y = 0.0f;
    pipelineBuilder.viewport.width = (float) _bs_window._windowExtent.width;
    pipelineBuilder.viewport.height = (float) _bs_window._windowExtent.height;
    pipelineBuilder.viewport.minDepth = 0.0f;
    pipelineBuilder.viewport.maxDepth = 1.0f;

    pipelineBuilder.scissor.offset = {0, 0};
    pipelineBuilder.scissor.extent = _bs_window._windowExtent;

    pipelineBuilder.viewportStateInfo = vkinit::viewportStateCreateInfo(&pipelineBuilder.viewport, &pipelineBuilder.scissor);
    pipelineBuilder.rasterizationStateInfo = vkinit::rasterizationStateCreateInfo();
    pipelineBuilder.multisampleStateInfo = vkinit::multisampleStateCreateInfoInfo();
    pipelineBuilder.depthStencilStateInfo = vkinit::depthStencilStateCreateInfo(true, true, VK_COMPARE_OP_LESS_OR_EQUAL);
    pipelineBuilder.colorBlendInfo = vkinit::colorBlendStateCreateInfo(&attachment);
    pipelineBuilder.pipelineLayout = genericPipelineLayout;

    _redTrianglePipeline = pipelineBuilder.build_pipeline(_logicalDevice, _renderPass);

    pipelineBuilder.shaderStages.clear();

    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, RGBvertexModule));
    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, RGBfragmentModule));

    VK_CHECK(vkCreatePipelineLayout(_logicalDevice, &pipelineLayoutInfo, nullptr, &genericPipelineLayout));

    pipelineBuilder.pipelineLayout = genericPipelineLayout;

    RGBTrianglePipeline = pipelineBuilder.build_pipeline(_logicalDevice, _renderPass);

    VertexInputDescription vertexDescription = Vertex::getVertexDescription();

    //connect the pipeline builder vertex input info to the one we get from Vertex
    pipelineBuilder.vertexInputStateInfo.pVertexAttributeDescriptions = vertexDescription.attributes.data();
    pipelineBuilder.vertexInputStateInfo.vertexAttributeDescriptionCount = vertexDescription.attributes.size();

    pipelineBuilder.vertexInputStateInfo.pVertexBindingDescriptions = vertexDescription.bindings.data();
    pipelineBuilder.vertexInputStateInfo.vertexBindingDescriptionCount = vertexDescription.bindings.size();

    //clear the shader stages for the builder
    pipelineBuilder.shaderStages.clear();

    //compile mesh vertex shader


    VkShaderModule meshVertShader;
    if (!load_shader("../shaders/tri_mesh.vert.spv", &meshVertShader))
    {
        std::cout << "Error when building the triangle vertex shader module" << std::endl;
    }
    else {
        std::cout << "Red Triangle vertex shader successfully loaded" << std::endl;
    }

    //add the other shaders
    pipelineBuilder.shaderStages.push_back(
            vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, meshVertShader));

    //make sure that triangleFragShader is holding the compiled colored_triangle.frag
    pipelineBuilder.shaderStages.push_back(
            vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, RGBfragmentModule));

    pipelineBuilder.pipelineLayout = _meshPipelineLayout;

    //build the mesh triangle pipeline
    _meshPipeline = pipelineBuilder.build_pipeline(_logicalDevice, _renderPass);
    create_material(_meshPipeline, _meshPipelineLayout, "defaultmesh");

    vkDestroyShaderModule(_logicalDevice, meshVertShader, nullptr);
    vkDestroyShaderModule(_logicalDevice, _redfragmentModule, nullptr);
    vkDestroyShaderModule(_logicalDevice, _redvertexModule, nullptr);
    vkDestroyShaderModule(_logicalDevice, RGBfragmentModule, nullptr);
    vkDestroyShaderModule(_logicalDevice, RGBvertexModule, nullptr);

    _mainDeletionQueue.push_function([=]()
                                     {
                                         vkDestroyPipeline(_logicalDevice, _redTrianglePipeline,nullptr);
                                         vkDestroyPipeline(_logicalDevice, RGBTrianglePipeline, nullptr);
                                         vkDestroyPipeline(_logicalDevice, _meshPipeline, nullptr);

                                         vkDestroyPipelineLayout(_logicalDevice, genericPipelineLayout, nullptr);
                                         vkDestroyPipelineLayout(_logicalDevice, _meshPipelineLayout, nullptr);
                                     });

    cout << "IT FUCKING WORKS\n";
}