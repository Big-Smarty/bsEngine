
# Add source to this project's executable.
add_executable(bsEngine
    main.cpp
    vk_engine.cpp
        vk_engine.hpp
        vk_types.hpp
    vk_initializers.cpp
        vk_initializers.hpp main.hpp window.cpp window.hpp vk_setup.cpp bs_swapchain.cpp vk_commands.cpp vk_renderpass.cpp bs_draw.cpp bs_frametime.cpp bs_load_shaders.cpp vk_pipelines.cpp pipeline_builder.cpp pipeline_builder.h)


set_property(TARGET bsEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")

target_include_directories(bsEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(bsEngine vkbootstrap vma glm tinyobjloader imgui stb_image)

target_link_libraries(bsEngine Vulkan::Vulkan sdl2)

add_dependencies(bsEngine Shaders)
