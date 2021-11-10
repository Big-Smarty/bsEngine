// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "main.hpp"
#include "window.hpp"

class bsEngine {
public:

    //VARIABLES
    //basic setup variables
    VkInstance _instance; //load core vulkan structures
    VkDebugUtilsMessengerEXT _debug_messenger; //debug messenger
    VkPhysicalDevice _chosenGPU; //handle to the chosen GPU
    VkDevice _logicalDevice; //logical vulkan device
    VkSurfaceKHR _surface; //surface used to display things on
    bsWindow _bs_window;

    VkSurfaceCapabilitiesKHR _surfaceCapabilities = {};

    //needed for frametime calculator
    std::chrono::time_point<std::chrono::high_resolution_clock> last_time;

    //swapchain variables
    VkSwapchainKHR _swapchain; //creates the swapchain
    VkFormat _swapchainImageFormat; //variable to store the image format of each image
    std::vector<VkImage> _swapchainImages; //swapchain array to store the images
    std::vector<VkImageView> _swapchainImageViews; //array to store the image vires from the swapchain
    vkb::InstanceBuilder builder;

    VkQueue _graphicsQueue; //queue which is going to have commands submitted to
    uint32_t _graphicsQueueFamily; //family of that queue

    VkCommandPool _commandPool; //the commandpool to manage command buffer and stuff
    VkCommandBuffer _mainCommandBuffer; //commandbuffer to store commands

    VkRenderPass  _renderPass;
    std::vector<VkFramebuffer> _framebuffers;

    //sync stuff
    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;

    VkPipelineLayout _trianglePipelineLayout;
    VkPipeline _trianglePipeline;

    VkViewport _viewport;
    VkRect2D _scissor;

	bool _isInitialized{ false };
	float _frameNumber {0};

    //FUNCTIONS

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

private:
    //REQUIRED
    void init_vulkan();

    void init_swapchain();

    void init_commands();

    void init_default_renderpass();

    void init_framebuffer();

    void init_sync_structures();

    void init_pipelines();

    //ADDITIONAL FEATURES
    std::optional<uint32_t> frametimeCounter();

    std::optional<VkShaderModule> load_shader(const char* shaderPath, VkShaderModule* outShaderModule);

    //WIP
    /*void setup_cmd_buffer();

    void initial_frame_setup();*/
};
