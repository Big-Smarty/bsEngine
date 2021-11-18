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

constexpr unsigned int FRAME_OVERLAP = 2;

struct CamState
{

    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camPos = {0,0,10};
    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 projection;
    glm::mat4 viewProj;
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);

    glm::vec3 camMovement = {0.0f, 0.0f, 0.0f};
    float speed = 15.0f;

    float pitch = 0;
    float yaw = -450;

    glm::vec3 direction;

};

struct GPUCameraData
{
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 viewproj;
};

struct GPUSceneData
{
    glm::vec4 fogColor;
    glm::vec4 fogDistances;
    glm::vec4 ambientColor;
    glm::vec4 sunlightDirection;
    glm::vec4 sunlightColor;
};

struct InputValues
{
    float* conGyro;

    float xOffset = 0;
    float yOffset = 0;
    float conRightX = 0;
    float conRightY = 0;
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

struct FrameData
{
    //sync stuff
    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;

    VkCommandPool _commandPool; //the commandpool to manage command buffer and stuff
    VkCommandBuffer _mainCommandBuffer; //commandbuffer to store commands

    AllocatedBuffer cameraBuffer; //VRAM buffer containing all the camera data
    VkDescriptorSet globalDescriptor;
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

    VkRenderPass  _renderPass;
    std::vector<VkFramebuffer> _framebuffers;
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

    //storing the frame data
    FrameData oFrameData[FRAME_OVERLAP];
    //getting current frame data
    FrameData& getCurrentFrame();
    //additions like framecounter (method to use this will be improved later on
    AdditionalVariables oAdditions;
    //essentials like instance, logical device, so on
    VulkanEssentials oVkEssentials;
    //controllerhandling uh
    GamePadHandling oControllerHandling;
    //stores all inputs
    InputValues oInput;
    //window object
    bsWindow oWindow;

    GPUSceneData sceneParameters;
    AllocatedBuffer sceneParametersBuffer;

    VkPipelineLayout genericPipelineLayout;

    VkPipelineLayout meshPipelineLayout;
    VkPipeline meshPipeline;

    Mesh monkeyMesh;

    DeletionQueue mainDeletionQueue;

    VkPhysicalDeviceProperties _deviceProperties;

    VmaAllocator allocator;

    VkImageView depthImageView;
    AllocatedImage depthImage;

    //depth image format
    VkFormat depthFormat;

    //default array for renderable objects
    std::vector<RenderObject> renderables;

    InputMouse mouseInput;

    std::unordered_map<std::string,Material> materials;
    std::unordered_map<std::string,Mesh> meshes;

    VkDescriptorSetLayout globalSetLayout;
    VkDescriptorPool descriptorPool;

    float frametime = 0;
    CamState camState = {};

    bool bQuit = {false};

	bool bIsInitialized{false };
	int frameNumber {0};

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

    void init_descriptors();

    size_t pad_uniform_buffer_size(size_t originalSize);

    AllocatedBuffer createBuffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memUsage);

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
