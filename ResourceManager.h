//
// Created by rostard on 17.12.17.
//

#ifndef DORMENGINE_RESOURCEMANAGER_H
#define DORMENGINE_RESOURCEMANAGER_H


#include <map>
#include "Shader.h"
#include "Texture.h"

class ResourceManager {
public:
    static Shader* loadShader(const std::string& name, const std::string& vsFilename, const std::string& fsFilename, const std::string& gsFilename = "");
    static Shader* getShader(const std::string& name);

    static Texture* loadTexture(const std::string& name, const std::string& filename, bool srgb = false);
    static Texture* getTexture(const std::string& name);

    //TODO: cubemap loader
    //TODO: mesh loader


private:
    static std::map<unsigned int, Shader> shaders;
    static std::map<unsigned int, Texture> textures;
};


#endif //DORMENGINE_RESOURCEMANAGER_H
