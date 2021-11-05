// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <main.h>

class bsEngine {
public:

    //basic setup variables
    VkInstance _instance; //load core vulkan structures
    VkDebugUtilsMessengerEXT _debug_messenger; //debug messenger
    VkPhysicalDevice _chosenGPU; //handle to the chosen GPU
    VkDevice _device; //logical vulkan device
    VkSurfaceKHR _surface; //surface used to display things on
    bsWindow _bs_window;

    //swapchain variables
    VkSwapchainKHR _swapchain; //creates the swapchain
    VkFormat _swapchainImageFormat; //variable to store the image format of each image
    std::vector<VkImage> _swapchainImages; //swapchain array to store the images
    std::vector<VkImageView> _swapchainImageViews; //array to store the image vires from the swapchain


	bool _isInitialized{ false };
	int _frameNumber {0};

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

private:
    void init_vulkan();

    void init_swapchain();
};
