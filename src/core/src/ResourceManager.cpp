//
// Created by rostard on 17.12.17.
//

#include "../include/ResourceManager.h"
#include "../include/SID.h"
#include "../include/ShaderLoader.h"
#include "../include/TextureLoader.h"

std::map<unsigned int, Shader> ResourceManager::shaders = std::map<unsigned int, Shader>();
std::map<unsigned int, Texture> ResourceManager::textures = std::map<unsigned int, Texture>();


Shader *
ResourceManager::loadShader(const std::string &name, const std::string &vsFilename, const std::string &fsFilename,
                            const std::string &gsFilename) {
    unsigned int id = SID(name);
    if(shaders.find(id) != shaders.end()){
        return getShader(name);
    }
    shaders[id] = ShaderLoader::Load(vsFilename, fsFilename, gsFilename);
    return &shaders[id];
}

Shader *ResourceManager::getShader(const std::string &name) {
    unsigned int id = SID(name);
    return &shaders.at(id);
}


Texture *ResourceManager::loadTexture(const std::string &name, const std::string &filename, bool srgb) {
    unsigned int id = SID(name);
    if(textures.find(id) != textures.end()){
        return getTexture(name);
    }
    textures[id] = TextureLoader::Load(filename, srgb);
    return &textures.at(id);
}

Texture *ResourceManager::getTexture(const std::string &name) {
    unsigned int id = SID(name);
    return &textures.at(id);
}
