//
// Created by rostard on 17.12.17.
//

#include <algorithm>
#include "ShaderLoader.h"



Shader ShaderLoader::Load(const std::string &vsFilename, const std::string &fsFilename, const std::string &gsFilename) {

    Shader shader;

    std::string vsSource = ReadFile(vsFilename);
    shader.addVertexShader(vsSource);

    std::string fsSource = ReadFile(fsFilename);
    shader.addFragmentShader(fsSource);

    if(gsFilename != ""){
        std::string gsSource = ReadFile(gsFilename);
        shader.addGeometryShader(gsSource);
    }

    shader.linkProgram();

    return shader;
}

std::string ShaderLoader::ReadFile(const std::string &filename) {
    const std::string INCLUDE_DIRECTIVE = "#include";
    std::ifstream file;

    file.open("shaders/" + filename);

    if(!file.is_open()){
        Log::Message("error loading file " + filename, LOG_ERROR);
        exit(1);
    }
    std::string res;
    while(!file.eof()){
        std::string string;
        std::getline(file, string);
        if(string.empty())continue;
        if(string.substr(0, INCLUDE_DIRECTIVE.size()) == INCLUDE_DIRECTIVE){
            string = ReadFile(string.substr(string.find_first_of("\"")+1, string.find_last_of("\"") - string.find_first_of("\"")-1));
        }
        res += string + "\n";
    }
    file.close();

    return res;
}
