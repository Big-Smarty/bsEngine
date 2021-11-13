//
// Created by bigsmarty on 11/5/21.
//

#pragma once

//MACROS
#define VK_CHECK(x)                                                 \
	do                                                              \
	{                                                               \
		VkResult err = x;                                           \
		if (err)                                                    \
		{                                                           \
			std::cout <<"Detected Vulkan error: " << err << std::endl; \
			abort();                                                \
		}                                                           \
	} while (0)

//STANDARD LIBRARIES
#include <iostream>
#include <vector>
#include <cassert>
#include <optional>
#include <chrono>
#include <fstream>
#include <functional>
#include <deque>

//THIRD PARTY LIBRARIES

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <setup/vk_types.h>
#include <setup/vk_initializers.h>
#include <vulkan/vulkan.h>

#include <VkBootstrap.h>
