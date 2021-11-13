//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <vk_engine.h>

using namespace std;

void bsEngine::init_swapchain()
{

    vkb::SwapchainBuilder swapchainBuilder{_chosenGPU, _logicalDevice, _surface};

    vkb::Swapchain vkbSwapchain = swapchainBuilder
            .use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_RELAXED_KHR)
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

    VkExtent3D depthImageExtent =
            {

                    _bs_window._windowExtent.width,
                    _bs_window._windowExtent.height,
                    1
            };

    _depthFormat = VK_FORMAT_D32_SFLOAT;

    VkImageCreateInfo dimg_info = vkinit::imageCreateInfo(_depthFormat, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, depthImageExtent);

    VmaAllocationCreateInfo dimg_allocinfo = {

            .usage = VMA_MEMORY_USAGE_GPU_ONLY,
            .requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    };

    vmaCreateImage(_allocator, &dimg_info, &dimg_allocinfo, &_depthImage._image, &_depthImage._allocation, nullptr);

    VkImageViewCreateInfo dview_info = vkinit::imageViewCreateInfo(_depthFormat, _depthImage._image, VK_IMAGE_ASPECT_DEPTH_BIT);

    VK_CHECK(vkCreateImageView(_logicalDevice, &dview_info, nullptr, &_depthImageView));

    _mainDeletionQueue.push_function([=]()
    {
        vkDestroySwapchainKHR(_logicalDevice, _swapchain, nullptr);

        vkDestroyImageView(_logicalDevice, _depthImageView, nullptr);
        vmaDestroyImage(_allocator, _depthImage._image, _depthImage._allocation);
        });

}