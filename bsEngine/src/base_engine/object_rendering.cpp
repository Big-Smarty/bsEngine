//
// Created by bigsmarty on 11/12/21.
//

#include <base_engine/vk_engine.h>
#include <main.h>

Material* bsEngine::create_material(VkPipeline pipeline, VkPipelineLayout layout, const std::string &name)
{
    Material mat = {
            .pipeline = pipeline,
            .pipelineLayout = layout
    };
    materials[name] = mat;
    return &materials[name];
}

Material* bsEngine::get_material(const std::string &name)
{
    auto it = materials.find(name);
    if (it == materials.end())
    {
        return nullptr;
    }
    else
    {
        return &(*it).second;
    }
}

Mesh* bsEngine::get_mesh(const std::string &name)
{
    auto it = meshes.find(name);
    if (it == meshes.end())
    {
        return nullptr;
    }
    else
    {
        return &(*it).second;
    }
}
