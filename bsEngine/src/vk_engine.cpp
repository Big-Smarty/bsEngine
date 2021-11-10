
#include "main.hpp"

using namespace std;

void bsEngine::init()
{
    init_vulkan();
    cout << "Initialised vulkan stuff without issues\n";

    init_swapchain();
    cout << "initialised the swapchain without issues\n";

    init_commands(); //initialise graphics commands stuff
    cout << "GPU commands stuff was initialized successfully\n";

    init_default_renderpass();
    cout << "Renderpass was initialised successfully\n";

    init_framebuffer();
    cout << "Framebuffer was initialised successfully\n";

    init_sync_structures();
    cout << "Sync structures were initialised successfully!\n";

    init_pipelines();
    cout << "Pipelines were initialised successfully!\n";
	
	//everything went fine
	_isInitialized = true;
    cout << "the engine was initialised without issues\n";
}
void bsEngine::cleanup()
{	
	if (_isInitialized) {

        vkDestroySemaphore(_logicalDevice, _renderSemaphore, nullptr);
        vkDestroySemaphore(_logicalDevice, _presentSemaphore, nullptr);
        vkDestroyFence(_logicalDevice, _renderFence, nullptr);

        vkDestroyCommandPool(_logicalDevice, _commandPool, nullptr);

        vkDestroySwapchainKHR(_logicalDevice, _swapchain, nullptr);

        vkDestroyRenderPass(_logicalDevice, _renderPass, nullptr);

        //destroy swapchain resources
        for (auto & _swapchainImageView : _swapchainImageViews)
        {
            vkDestroyImageView(_logicalDevice, _swapchainImageView, nullptr);
        }
        vkDestroyDevice(_logicalDevice, nullptr);
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
        vkDestroyInstance(_instance, nullptr);
		
		SDL_DestroyWindow(_bs_window._window);

        cout << "cleanup ran without issues\n";
	}
}


void bsEngine::run()
{
	SDL_Event e;
	bool bQuit = false;

	//main loop
	while (!bQuit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//close the window when user alt-f4s or clicks the X button			
			if (e.type == SDL_QUIT) bQuit = true;
		}

		draw();
	}

}

void bsEngine::init_sync_structures()
{

    VkFenceCreateInfo fenceCreateInfo = {

            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .pNext = nullptr,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    VK_CHECK(vkCreateFence(_logicalDevice, &fenceCreateInfo, nullptr, &_renderFence));

    VkSemaphoreCreateInfo semaphoreCreateInfo = {

        VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0
    };

    VK_CHECK(vkCreateSemaphore(_logicalDevice, &semaphoreCreateInfo, nullptr, &_renderSemaphore));
    VK_CHECK(vkCreateSemaphore(_logicalDevice, &semaphoreCreateInfo, nullptr, &_presentSemaphore));
}

