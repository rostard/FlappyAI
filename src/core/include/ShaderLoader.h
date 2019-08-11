//
// Created by rostard on 17.12.17.
//

#ifndef DORMENGINE_SHADERLOADER_H
#define DORMENGINE_SHADERLOADER_H


#include <sstream>
#include <fstream>
#include "../include/Shader.h"
#include "../include/Log.h"

class ShaderLoader {
public:
    ShaderLoader() = delete;

    static Shader Load(const std::string& vsFilename, const std::string& fsFilename, const std::string& gsFilename = "");

    static std::string ReadFile(const std::string& filename);
};


#endif //DORMENGINE_SHADERLOADER_H
