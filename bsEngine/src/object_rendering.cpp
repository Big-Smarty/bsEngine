//
// Created by bigsmarty on 11/12/21.
//

#include <vk_engine.h>
#include <main.h>

Material* bsEngine::create_material(VkPipeline pipeline, VkPipelineLayout layout, const std::string &name)
{
    Material mat = {
            .pipeline = pipeline,
            .pipelineLayout = layout
    };
    _materials[name] = mat;
    return &_materials[name];
}

Material* bsEngine::get_material(const std::string &name)
{
    auto it = _materials.find(name);
    if (it == _materials.end())
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
    auto it = _meshes.find(name);
    if (it == _meshes.end())
    {
        return nullptr;
    }
    else
    {
        return &(*it).second;
    }
}