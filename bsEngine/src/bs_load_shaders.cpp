#include "main.hpp"
#include "vk_engine.hpp"

using namespace std;

std::optional<VkShaderModule> bsEngine::load_shader(const char* shaderPath, VkShaderModule* outShaderModule)
{

    ifstream shaderStream(shaderPath, ios::ate | ios::binary);

    if (!shaderStream.is_open())
    {

        cout << "Couldn't open specified shader path!\n";
        return nullopt;
    }

    size_t shaderSize = shaderStream.tellg();
    cout << "Size of shader: " << shaderSize << "\n";

    vector<uint32_t> shaderBuffer(shaderSize / sizeof(uint32_t));

    shaderStream.seekg(0);
    shaderStream.read((char*)shaderBuffer.data(), shaderSize);

    shaderStream.close();

    VkShaderModuleCreateInfo shaderInfo = vkinit::createShaderInfo(shaderSize, shaderBuffer.data());
    cout << "Shadersize of shaderinfo: " << shaderInfo.codeSize << endl;

    vkCreateShaderModule(_logicalDevice, &shaderInfo, nullptr, outShaderModule);

    return *outShaderModule;

}