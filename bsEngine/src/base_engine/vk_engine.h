// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "main.h"
#include "windowing/window.h"
#include "setup/vk_types.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "vk_mem_alloc.h"
#include <resource_loading/vk_mesh.h>
#include <io/mouse_input.h>
#include "../io/controller_input.h"

struct CamState
{

    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camPos = {0,0,10};
    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 projection;
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::vec3 camMovement = {0.0f, 0.0f, 0.0f};
    float speed = 15.0f;

    float pitch = 0;
    float yaw = -450;

    glm::vec3 direction;

};

struct InputValues
{
    float xOffset;
    float yOffset;
    float conRightX;
    float conRightY;
};

struct Material
{
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
};

struct RenderObject
{
    Mesh* mesh;
    Material* material;
    glm::mat4 transformMatrix;
};

struct AllocatedImage
{

    VkImage _image;
    VmaAllocation _allocation;

};

struct MeshPushConstants
{
    glm::vec4 data;
    glm::mat4 render_matrix;
};

struct VulkanEssentials
{
    VkInstance _instance; //load core vulkan structures
    vkb::InstanceBuilder builder;

    VkDebugUtilsMessengerEXT _debug_messenger; //debug messenger

    VkPhysicalDevice _chosenGPU; //handle to the chosen GPU
    VkDevice _logicalDevice; //logical vulkan device

    VkSurfaceKHR _surface; //surface used to display things on
    VkSurfaceCapabilitiesKHR _surfaceCapabilities;

    VkSwapchainKHR _swapchain; //creates the swapchain
    VkFormat _swapchainImageFormat; //variable to store the image format of each image
    std::vector<VkImage> _swapchainImages; //swapchain array to store the images
    std::vector<VkImageView> _swapchainImageViews; //array to store the image vires from the swapchain

    VkQueue _graphicsQueue; //queue which is going to have commands submitted to
    uint32_t _graphicsQueueFamily; //family of that queue

    VkCommandPool _commandPool; //the commandpool to manage command buffer and stuff
    VkCommandBuffer _mainCommandBuffer; //commandbuffer to store commands

    VkRenderPass  _renderPass;
    std::vector<VkFramebuffer> _framebuffers;

    //sync stuff
    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;
};

struct AdditionalVariables
{
    std::chrono::time_point<std::chrono::high_resolution_clock> last_time;
};

struct DeletionQueue
{

    std::deque<std::function<void()>> deletors;

    void push_function(std::function<void()>&& function)
    {
        deletors.push_back((function));
    }

    void flush()
    {

        for (auto it = deletors.rbegin(); it != deletors.rend(); it++)
        {
            (*it)();
        }
        deletors.clear();

    }

};

class bsEngine {
public:

    AdditionalVariables additions;
    VulkanEssentials vkEssentials;
    GamePadHandling controllerHandling;
    InputValues inputValues;
    bsWindow _bs_window;

    VkPipelineLayout genericPipelineLayout;

    VkPipelineLayout _meshPipelineLayout;
    VkPipeline _meshPipeline;
    Mesh _triangleMesh;

    Mesh _monkeyMesh;

    DeletionQueue _mainDeletionQueue;

    VmaAllocator _allocator;

    VkImageView _depthImageView;
    AllocatedImage _depthImage;

    //depth image format
    VkFormat _depthFormat;

    //default array for renderable objects
    std::vector<RenderObject> _renderables;

    InputMouse mouseInput;

    std::unordered_map<std::string,Material> _materials;
    std::unordered_map<std::string,Mesh> _meshes;

    float _frametime = 0;
    CamState camState = {};

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

    void load_meshes();

    void init_scene();

    void upload_mesh(Mesh& mesh);

    void camera();

    //ADDITIONAL FEATURES
    float frametimeCounter();

    std::optional<VkShaderModule> load_shader(const char* shaderPath, VkShaderModule* outShaderModule);

    //create material and add it to the unordered map
    Material* create_material(VkPipeline pipeline, VkPipelineLayout layout, const std::string& name);

    //returns nullptr if it cant be found
    Material* get_material(const std::string& name);

    //returns nullptr if it cant be found
    Mesh* get_mesh(const std::string& name);

    //the draw function for the objects
    void draw_objects(VkCommandBuffer cmd, RenderObject* first, int count);

    //WIP
    /*void setup_cmd_buffer();

    void initial_frame_setup();*/
};
