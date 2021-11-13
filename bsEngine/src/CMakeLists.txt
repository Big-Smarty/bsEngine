
# Add source to this project's executable.
add_executable(bsEngine
    main.cpp
        base_engine/vk_engine.cpp
        base_engine/vk_engine.h
        setup/vk_types.h
        setup/vk_initializers.cpp
        setup/vk_initializers.h main.h windowing/window.cpp windowing/window.h setup/vk_setup.cpp setup/bs_swapchain.cpp setup/vk_commands.cpp setup/vk_renderpass.cpp base_engine/bs_draw.cpp additions/bs_frametime.cpp resource_loading/bs_load_shaders.cpp setup/vk_pipelines.cpp setup/pipeline_builder.cpp setup/pipeline_builder.h resource_loading/vk_mesh.cpp resource_loading/vk_mesh.h resource_loading/mesh_loading.cpp base_engine/object_rendering.cpp resource_loading/bs_scene.cpp io/bs_camera.cpp io/mouse_input.cpp io/mouse_input.h)


set_property(TARGET bsEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")

target_include_directories(bsEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(bsEngine vkbootstrap vma glm tinyobjloader imgui stb_image)

target_link_libraries(bsEngine Vulkan::Vulkan sdl2)

add_dependencies(bsEngine Shaders)
