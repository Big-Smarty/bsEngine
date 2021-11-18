//
// Created by bigsmarty on 11/7/21.
//

#include "main.h"
#include "base_engine/vk_engine.h"
#include "setup/pipeline_builder.h"
#include "setup/vk_initializers.h"

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
    meshPipelineLayoutInfo.setLayoutCount = 1;
    meshPipelineLayoutInfo.pSetLayouts = &globalSetLayout;

    VK_CHECK(vkCreatePipelineLayout(oVkEssentials._logicalDevice, &meshPipelineLayoutInfo, nullptr, &meshPipelineLayout));

    VkShaderModule RGBfragmentModule;
    if (load_shader("../shaders/rgb_triangle.frag.spv", &RGBfragmentModule) != nullopt) {
        cout << "Successfully loaded the fragment shader module!\n";
    } else {
        cerr << "Failed to load the fragment shader module!\n";
        abort();
    }
    VkShaderModule meshVertShader;
    if (load_shader("../shaders/tri_mesh.vert.spv", &meshVertShader))
    {
        std::cout << "Red Triangle vertex shader successfully loaded" << std::endl;
    }
    else {
        cerr << "Error when building the triangle vertex shader module" << std::endl;
        abort();
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = vkinit::pipelineLayoutCreateInfo();

    VK_CHECK(vkCreatePipelineLayout(oVkEssentials._logicalDevice, &pipelineLayoutInfo, nullptr, &genericPipelineLayout));

    PipelineBuilder pipelineBuilder;

    VkPipelineColorBlendAttachmentState attachment = vkinit::createColorBlendAttachmentState();

    pipelineBuilder.vertexInputStateInfo = vkinit::vertexInputStateCreateInfo();
    pipelineBuilder.inputAssemblyStateInfo = vkinit::inputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    pipelineBuilder.viewport.x = 0.0f;
    pipelineBuilder.viewport.y = 0.0f;
    pipelineBuilder.viewport.width = (float) oWindow._windowExtent.width;
    pipelineBuilder.viewport.height = (float) oWindow._windowExtent.height;
    pipelineBuilder.viewport.minDepth = 0.0f;
    pipelineBuilder.viewport.maxDepth = 1.0f;

    pipelineBuilder.scissor.offset = {0, 0};
    pipelineBuilder.scissor.extent = oWindow._windowExtent;

    pipelineBuilder.viewportStateInfo = vkinit::viewportStateCreateInfo(&pipelineBuilder.viewport, &pipelineBuilder.scissor);
    pipelineBuilder.rasterizationStateInfo = vkinit::rasterizationStateCreateInfo();
    pipelineBuilder.multisampleStateInfo = vkinit::multisampleStateCreateInfoInfo();
    pipelineBuilder.depthStencilStateInfo = vkinit::depthStencilStateCreateInfo(true, true, VK_COMPARE_OP_LESS_OR_EQUAL);
    pipelineBuilder.colorBlendInfo = vkinit::colorBlendStateCreateInfo(&attachment);
    pipelineBuilder.pipelineLayout = genericPipelineLayout;

    pipelineBuilder.shaderStages.push_back(vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, RGBfragmentModule));

    VK_CHECK(vkCreatePipelineLayout(oVkEssentials._logicalDevice, &pipelineLayoutInfo, nullptr, &genericPipelineLayout));

    pipelineBuilder.pipelineLayout = genericPipelineLayout;

    VertexInputDescription vertexDescription = Vertex::getVertexDescription();

    //connect the pipeline builder vertex input info to the one we get from Vertex
    pipelineBuilder.vertexInputStateInfo.pVertexAttributeDescriptions = vertexDescription.attributes.data();
    pipelineBuilder.vertexInputStateInfo.vertexAttributeDescriptionCount = vertexDescription.attributes.size();

    pipelineBuilder.vertexInputStateInfo.pVertexBindingDescriptions = vertexDescription.bindings.data();
    pipelineBuilder.vertexInputStateInfo.vertexBindingDescriptionCount = vertexDescription.bindings.size();

    pipelineBuilder.shaderStages.clear();
    //add the other shaders
    pipelineBuilder.shaderStages.push_back(
            vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, meshVertShader));

    //make sure that triangleFragShader is holding the compiled colored_triangle.frag
    pipelineBuilder.shaderStages.push_back(
            vkinit::shaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, RGBfragmentModule));

    pipelineBuilder.pipelineLayout = meshPipelineLayout;

    //build the mesh triangle pipeline
    meshPipeline = pipelineBuilder.build_pipeline(oVkEssentials._logicalDevice, oVkEssentials._renderPass);
    create_material(meshPipeline, meshPipelineLayout, "defaultmesh");

    vkDestroyShaderModule(oVkEssentials._logicalDevice, meshVertShader, nullptr);
    vkDestroyShaderModule(oVkEssentials._logicalDevice, RGBfragmentModule, nullptr);

    mainDeletionQueue.push_function([=]()
                                     {
                                         vkDestroyPipeline(oVkEssentials._logicalDevice, meshPipeline, nullptr);
                                         vkDestroyPipelineLayout(oVkEssentials._logicalDevice, genericPipelineLayout, nullptr);
                                         vkDestroyPipelineLayout(oVkEssentials._logicalDevice, meshPipelineLayout, nullptr);
                                     });

    cout << "IT FUCKING WORKS\n";
}