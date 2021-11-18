//
// Created by bigsmarty on 11/5/21.
//

#include "main.h"
#include <base_engine/vk_engine.h>

using namespace std;

void bsEngine::init_swapchain()
{

    vkb::SwapchainBuilder swapchainBuilder{oVkEssentials._chosenGPU, oVkEssentials._logicalDevice, oVkEssentials._surface};

    vkb::Swapchain vkbSwapchain = swapchainBuilder
            .use_default_format_selection()
            .set_desired_present_mode(VK_PRESENT_MODE_FIFO_RELAXED_KHR)
            .set_desired_extent(oWindow._windowExtent.width, oWindow._windowExtent.height)
            .build()
            .value();


    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(oVkEssentials._chosenGPU, oVkEssentials._surface, &oVkEssentials._surfaceCapabilities);
    cout << "max image count of the surface:" << oVkEssentials._surfaceCapabilities.maxImageCount << endl;

    vkbSwapchain.image_count = oVkEssentials._surfaceCapabilities.maxImageCount;

    //store the swapchain and its images
    oVkEssentials._swapchain = vkbSwapchain.swapchain;
    oVkEssentials._swapchainImages = vkbSwapchain.get_images().value();
    oVkEssentials._swapchainImageViews = vkbSwapchain.get_image_views().value();

    oVkEssentials._swapchainImageFormat = vkbSwapchain.image_format;

    VkExtent3D depthImageExtent =
            {

                    oWindow._windowExtent.width,
                    oWindow._windowExtent.height,
                    1
            };

    depthFormat = VK_FORMAT_D32_SFLOAT;

    VkImageCreateInfo dimg_info = vkinit::imageCreateInfo(depthFormat, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, depthImageExtent);

    VmaAllocationCreateInfo dimg_allocinfo = {

            .usage = VMA_MEMORY_USAGE_GPU_ONLY,
            .requiredFlags = VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    };

    vmaCreateImage(allocator, &dimg_info, &dimg_allocinfo, &depthImage._image, &depthImage._allocation, nullptr);

    VkImageViewCreateInfo dview_info = vkinit::imageViewCreateInfo(depthFormat, depthImage._image, VK_IMAGE_ASPECT_DEPTH_BIT);

    VK_CHECK(vkCreateImageView(oVkEssentials._logicalDevice, &dview_info, nullptr, &depthImageView));

    mainDeletionQueue.push_function([=]()
    {
        vkDestroySwapchainKHR(oVkEssentials._logicalDevice, oVkEssentials._swapchain, nullptr);

        vkDestroyImageView(oVkEssentials._logicalDevice, depthImageView, nullptr);
        vmaDestroyImage(allocator, depthImage._image, depthImage._allocation);
        });

}