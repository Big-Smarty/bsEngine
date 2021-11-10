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

//THIRD PARTY LIBRARIES

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vk_types.hpp>
#include <vk_initializers.hpp>
#include <vulkan/vulkan.h>

#include <VkBootstrap.h>

//CUSTOM HEADERS
#include <vk_engine.hpp>
#include <vk_types.hpp>
#include <vk_initializers.hpp>
#include <window.hpp>
