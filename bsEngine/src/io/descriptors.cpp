//
// Created by bigsmarty on 11/16/21.
//

#include "../main.h"
#include "../base_engine/vk_engine.h"

using namespace std;

void bsEngine::init_descriptors()
{
    const size_t sceneParameterBufferSize = FRAME_OVERLAP * pad_uniform_buffer_size(sizeof(GPUSceneData));
    sceneParametersBuffer = createBuffer(sceneParameterBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);

    //create descriptor pool that will hold 10 uniform buffers
    vector<VkDescriptorPoolSize> sizes = {{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}};

    VkDescriptorPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .maxSets = 10,
            .poolSizeCount = static_cast<uint32_t>(sizes.size()),
            .pPoolSizes = sizes.data()
    };

    vkCreateDescriptorPool(oVkEssentials._logicalDevice, &poolInfo, nullptr, &descriptorPool);

    //information about the binding
    VkDescriptorSetLayoutBinding camBufferBinding = {
            .binding = 0,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, //its a uniform buffer binding
            .descriptorCount = 1,
            .stageFlags = VK_SHADER_STAGE_VERTEX_BIT //...that is used from within a vertex shader
    };

    VkDescriptorSetLayoutCreateInfo setInfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .pNext = nullptr,
            .bindingCount = 1,
            .flags = 0,
            .pBindings = &camBufferBinding
    };

    vkCreateDescriptorSetLayout(oVkEssentials._logicalDevice, &setInfo, nullptr, &globalSetLayout);

    for (int i = 0; i < FRAME_OVERLAP; i++)
    {
        oFrameData[i].cameraBuffer = createBuffer(sizeof(GPUCameraData), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);

        //allocate one descriptor set per frame
        VkDescriptorSetAllocateInfo allocInfo = {
                .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                .pNext = nullptr,
                .descriptorPool = descriptorPool,
                .descriptorSetCount = 1,
                .pSetLayouts = &globalSetLayout,
        };

        vkAllocateDescriptorSets(oVkEssentials._logicalDevice, &allocInfo, &oFrameData[i].globalDescriptor);
    }

    for (int i = 0; i < FRAME_OVERLAP; i++)
    {
        VkDescriptorBufferInfo bufferInfo = {
                .buffer = oFrameData[i].cameraBuffer._buffer,
                .offset = 0,
                .range = sizeof(GPUCameraData),
        };
        VkWriteDescriptorSet writeSet = {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .pNext = nullptr,
                .dstSet = oFrameData[i].globalDescriptor,
                .dstBinding = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                .pBufferInfo = &bufferInfo
        };

        vkUpdateDescriptorSets(oVkEssentials._logicalDevice, 1, &writeSet, 0, nullptr);
    }
}