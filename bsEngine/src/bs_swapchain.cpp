//
// Created by bigsmarty on 11/5/21.
//

#include "main.hpp"

using namespace std;

void bsEngine::init_swapchain()
{

    vkb::SwapchainBuilder swapchainBuilder{_chosenGPU, _logicalDevice, _surface};

    vkb::Swapchain vkbSwapchain = swapchainBuilder
            .use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
            .set_desired_extent(_bs_window._windowExtent.width, _bs_window._windowExtent.height)
            .build()
            .value();


    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_chosenGPU, _surface, &_surfaceCapabilities);
    cout << "max image count of the surface:" << _surfaceCapabilities.maxImageCount << endl;

    vkbSwapchain.image_count = _surfaceCapabilities.maxImageCount;

    //store the swapchain and its images
    _swapchain = vkbSwapchain.swapchain;
    _swapchainImages = vkbSwapchain.get_images().value();
    _swapchainImageViews = vkbSwapchain.get_image_views().value();

    _swapchainImageFormat = vkbSwapchain.image_format;

}