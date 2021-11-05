//
// Created by bigsmarty on 11/5/21.
//

#include <main.h>

void bsEngine::init_vulkan()
{

    vkb::InstanceBuilder builder;

    //create the vulkan instance with basic debugging features
    auto inst_ret = builder.set_app_name("BS Engine")
            .request_validation_layers(true)
            .require_api_version(1, 1, 0)
            .use_default_debug_messenger()
            .build();

    vkb::Instance vkb_inst = inst_ret.value();

    //store the instance
    _instance = vkb_inst.instance;

    //store the debug messenger
    _debug_messenger = vkb_inst.debug_messenger;

    SDL_Vulkan_CreateSurface(_bs_window._window, _instance, &_surface);

    //use vkBootstrap to select a GPU with support for present and Vulkan => 1.1
    vkb::PhysicalDeviceSelector selector {vkb_inst};
    vkb::PhysicalDevice physicalDevice = selector
            .set_minimum_version(1, 1)
            .set_surface(_surface)
            .select()
            .value();

    //create the logical device thats going to be used
    vkb::DeviceBuilder deviceBuilder{physicalDevice};

    vkb::Device vkbDevice = deviceBuilder.build().value();

    //store the logical and physical device for later use
    _device = vkbDevice.device;
    _chosenGPU = physicalDevice.physical_device;

}