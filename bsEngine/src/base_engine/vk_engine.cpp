
#include <base_engine/vk_engine.h>

using namespace std;

void bsEngine::init()
{
    mouseInput.Initialize();
    mouseInput.Update();
    cout << "Mouse initialization was successful!\n";

    oControllerHandling.InitializeControllers();
    oControllerHandling.Update();
    cout << "Controller initialization was successful!\n";

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

    init_descriptors();
    cout << "Descriptors were initialized successfully!\n";

    init_pipelines();
    cout << "Pipelines were initialised successfully!\n";

    load_meshes();
    cout << "Meshes have been loaded successfully!\n";

    init_scene();
    cout << "Scene has been loaded successfully!\n";
	
	//everything went fine
	bIsInitialized = true;
    cout << "the engine was initialised without issues\n";
}
void bsEngine::cleanup()
{	
	if (bIsInitialized) {

        vkWaitForFences(oVkEssentials._logicalDevice, 1, &getCurrentFrame()._renderFence, true, 1000000000);

        mainDeletionQueue.flush();

        vkDestroySurfaceKHR(oVkEssentials._instance, oVkEssentials._surface, nullptr);
        vkDestroyDevice(oVkEssentials._logicalDevice, nullptr);
        vkDestroyInstance(oVkEssentials._instance, nullptr);
		
		SDL_DestroyWindow(oWindow._window);

        cout << "cleanup ran without issues\n";
	}
}


void bsEngine::run()
{
	SDL_Event e;

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
        oControllerHandling.Update();

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

    for (int i = 0; i < FRAME_OVERLAP; i++)
    {
        VK_CHECK(vkCreateFence(oVkEssentials._logicalDevice, &fenceCreateInfo, nullptr, &oFrameData[i]._renderFence));
        mainDeletionQueue.push_function([=]()
                                         {
                                             vkDestroyFence(oVkEssentials._logicalDevice, oFrameData[i]._renderFence, nullptr);
                                         });

        VkSemaphoreCreateInfo semaphoreCreateInfo = {

                .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0
        };

        VK_CHECK(vkCreateSemaphore(oVkEssentials._logicalDevice, &semaphoreCreateInfo, nullptr, &oFrameData[i]._renderSemaphore));
        VK_CHECK(vkCreateSemaphore(oVkEssentials._logicalDevice, &semaphoreCreateInfo, nullptr, &oFrameData[i]._presentSemaphore));

        mainDeletionQueue.push_function([=]()
                                         {
                                             vkDestroySemaphore(oVkEssentials._logicalDevice, oFrameData[i]._presentSemaphore, nullptr);
                                             vkDestroySemaphore(oVkEssentials._logicalDevice, oFrameData[i]._renderSemaphore, nullptr);
                                         });
    }

}

size_t bsEngine::pad_uniform_buffer_size(size_t originalSize)
{
    //calculate required alignment based on the minimum offset
    size_t minUboAlignment = _deviceProperties.limits.minUniformBufferOffsetAlignment;
    size_t alignedSize = originalSize;
    if (minUboAlignment > 0)
    {
        alignedSize = (alignedSize + minUboAlignment - 1) & ~(minUboAlignment - 1);
    }
    return alignedSize;
}
