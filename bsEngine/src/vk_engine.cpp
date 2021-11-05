
#include "vk_engine.h"

void bsEngine::init()
{
    init_vulkan();

    init_swapchain();
	
	//everything went fine
	_isInitialized = true;
}
void bsEngine::cleanup()
{	
	if (_isInitialized) {
		
		SDL_DestroyWindow(_bs_window._window);
	}
}

void bsEngine::draw()
{
	//nothing yet
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

