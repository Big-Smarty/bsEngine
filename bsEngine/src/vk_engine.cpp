
#include <vk_engine.h>

using namespace std;

void bsEngine::init()
{
    mouseInput.Initialize();
    mouseInput.Update();
    cout << "Mouse initialization was successful!\n";

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

    load_meshes();
    cout << "Meshes have been loaded successfully!\n";

    init_scene();
    cout << "Scene has been loaded successfully!\n";
	
	//everything went fine
	_isInitialized = true;
    cout << "the engine was initialised without issues\n";
}
void bsEngine::cleanup()
{	
	if (_isInitialized) {

        vkWaitForFences(_logicalDevice, 1, &_renderFence, true, 1000000000);

        _mainDeletionQueue.flush();

        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyDevice(_logicalDevice, nullptr);
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
			switch(e.type)
            {
                case SDL_QUIT:
                    bQuit = true;

            }

		}

        mouseInput.Update();

        camera();

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
    _mainDeletionQueue.push_function([=]()
                                     {
                                         vkDestroyFence(_logicalDevice, _renderFence, nullptr);
                                     });

    VkSemaphoreCreateInfo semaphoreCreateInfo = {

        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0
    };

    VK_CHECK(vkCreateSemaphore(_logicalDevice, &semaphoreCreateInfo, nullptr, &_renderSemaphore));
    VK_CHECK(vkCreateSemaphore(_logicalDevice, &semaphoreCreateInfo, nullptr, &_presentSemaphore));

    _mainDeletionQueue.push_function([=]()
                                     {
                                         vkDestroySemaphore(_logicalDevice, _presentSemaphore, nullptr);
                                         vkDestroySemaphore(_logicalDevice, _renderSemaphore, nullptr);
                                     });

}

