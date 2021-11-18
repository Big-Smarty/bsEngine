//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include "base_engine/vk_engine.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

using namespace std;

void bsEngine::init_vulkan()
{

    //create the vulkan instance with basic debugging features
    auto inst_ret = oVkEssentials.builder.set_app_name("BS Engine")
            .request_validation_layers(true)
            .require_api_version(1, 1, 0)
            .use_default_debug_messenger()
            .build();

    vkb::Instance vkb_inst = inst_ret.value();

    //store the instance
    oVkEssentials._instance = vkb_inst.instance;

    //store the debug messenger
    oVkEssentials._debug_messenger = vkb_inst.debug_messenger;

    SDL_Vulkan_CreateSurface(oWindow._window, oVkEssentials._instance, &oVkEssentials._surface);

    //use vkBootstrap to select a GPU with support for present and Vulkan => 1.1
    vkb::PhysicalDeviceSelector selector {vkb_inst};
    vkb::PhysicalDevice physicalDevice = selector
            .set_minimum_version(1, 1)
            .set_surface(oVkEssentials._surface)
            .select()
            .value();

    //create the logical device thats going to be used
    vkb::DeviceBuilder deviceBuilder{physicalDevice};

    vkb::Device vkbDevice = deviceBuilder.build().value();

    //store the logical and physical device for later use
    oVkEssentials._logicalDevice = vkbDevice.device;
    oVkEssentials._chosenGPU = physicalDevice.physical_device;

    vkGetPhysicalDeviceProperties(oVkEssentials._chosenGPU, &_deviceProperties);
    cout << "Devicetype of the chosen GPU: " << _deviceProperties.deviceType << std::endl;
    cout << "Minimum buffer alignment: " << _deviceProperties.limits.minUniformBufferOffsetAlignment << endl;

    //use vkBootstrap to find a suitable graphics queue
    oVkEssentials._graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
    oVkEssentials._graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();

    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo = {
            .physicalDevice = oVkEssentials._chosenGPU,
            .device = oVkEssentials._logicalDevice,
            .instance = oVkEssentials._instance,
    };

    vmaCreateAllocator(&allocatorInfo, &allocator);

}

