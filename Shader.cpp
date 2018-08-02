//
// Created by rostard on 14.12.17.
//

#include <GL/glew.h>
#include <unordered_map>
#include "Shader.h"
#include "utility/Log.h"


std::map<std::string, std::vector<uniformStruct>> parseStructs(const std::string& shaderCode){
    std::map<std::string, std::vector<uniformStruct>> result;


    unsigned long structStartPos = shaderCode.find("struct");
    while (structStartPos != -1){
        unsigned long brackets_start = shaderCode.find('{', structStartPos);
        unsigned long brackets_end = shaderCode.find('}', structStartPos);
        std::string structType = shaderCode.substr(structStartPos+7, brackets_start - structStartPos-7);


        unsigned long semicolonPos = shaderCode.find(';', structStartPos);
        while (semicolonPos!= -1 && semicolonPos < brackets_end){
            unsigned long whitespacePos = shaderCode.find_last_of(' ', semicolonPos);
            std::string uniformName = shaderCode.substr(whitespacePos+1, semicolonPos-whitespacePos-1);
            unsigned long whitespacePos2 = shaderCode.find_last_of(' ', whitespacePos-1);
            std::string uniformType = shaderCode.substr(whitespacePos2+1, whitespacePos-whitespacePos2-1);

            result[structType].push_back({uniformType, uniformName});

            semicolonPos = shaderCode.find(';', semicolonPos+1);
        }
        structStartPos = shaderCode.find("struct", structStartPos+1);
    }

    return result;
}


std::vector<uniformStruct> parseStructedUniform(const std::map<std::string, std::vector<uniformStruct>> &structs,
                                                const uniformStruct &uniform, const std::string prefix = ""){
    std::vector<uniformStruct> res;
    if(structs.find(uniform.type) == structs.end()){
        res.push_back({uniform.type, prefix+uniform.name});
    }
    else{
        for(auto i : structs.at(uniform.type)){
            std::vector<uniformStruct> ins = parseStructedUniform(structs, i, prefix + uniform.name + ".");
            res.insert(res.end(), ins.begin(), ins.end());
        }
    }
    return res;
}

std::vector<uniformStruct> parseUniforms(const std::map<std::string, std::vector<uniformStruct>>& structs, const std::string& shaderCode){
    std::vector<uniformStruct> result;

    unsigned long uniformStartPos = shaderCode.find("uniform");
    while (uniformStartPos != -1){
        unsigned long whitespacePos = shaderCode.find(' ', uniformStartPos+8);
        std::string uniformType = shaderCode.substr(uniformStartPos+8, whitespacePos - uniformStartPos-8);

        unsigned long whitespacePos2 = shaderCode.find(';', whitespacePos+1);
        std::string uniformName = shaderCode.substr(whitespacePos+1, whitespacePos2 - whitespacePos-1);

        std::vector<uniformStruct> parsed = parseStructedUniform(structs, {uniformType, uniformName});
        result.insert(result.end(), parsed.begin(), parsed.end());
        uniformStartPos = shaderCode.find("uniform", uniformStartPos+1);
    }

    return result;
};


Shader::Shader() {
    program = glCreateProgram();
}


Shader::Shader(const Shader &shader) {
    setProgram(shader.getProgram());
}


std::string shaderTypeToStr(int shaderType){
    std::string ret;
    switch (shaderType){
        case GL_VERTEX_SHADER:
            ret = "VERTEX_SHADER";
            break;
        case GL_FRAGMENT_SHADER:
            ret = "FRAGMENT_SHADER";
            break;
        case GL_GEOMETRY_SHADER:
            ret = "GEOMETRY_SHADER";
            break;
        default:
            ret = "UNKNOWN_SHADER";
    }
    return ret;
}

void Shader::addShader(const std::string &shaderSource, int shaderType) {
    auto st = parseStructs(shaderSource);
    auto uniforms = parseUniforms(st, shaderSource);

    this->uniforms.insert(this->uniforms.end(), uniforms.begin(), uniforms.end());

    unsigned int shader = glCreateShader(shaderType);
    const char* shaderCode = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderCode , nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if(!success){
        glGetShaderInfoLog(shader, 512, nullptr, &infoLog[0]);
        Log::Message(shaderTypeToStr(shaderType) +"::COMPILATION_FAILED\n" + std::string(infoLog), LOG_ERROR);
    }

    glAttachShader(program, shader);
}

void Shader::linkProgram() {
    glLinkProgram(program);

    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        Log::Message("SHADER::LINK_FAILED\n" + std::string(infoLog), LOG_ERROR);
    }

    glValidateProgram(program);

    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        Log::Message("SHADER::VALIDATION_FAILED\n" + std::string(infoLog), LOG_ERROR);
    }
}

void Shader::bind() {
    glUseProgram(program);
}

void Shader::addVertexShader(const std::string &shaderSource) {
    addShader(shaderSource, GL_VERTEX_SHADER);
}

void Shader::addFragmentShader(const std::string &shaderSource) {
    addShader(shaderSource, GL_FRAGMENT_SHADER);
}

void Shader::addGeometryShader(const std::string &shaderSource) {
    addShader(shaderSource, GL_GEOMETRY_SHADER);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

//void Shader::setMat4(const std::string &name, Matrix4f matrix) const {
//    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_TRUE, matrix.getM());
//}


void Shader::setVec2(const std::string &name, Vector2f vector) const {
    glUniform2f(glGetUniformLocation(program, name.c_str()), vector.getX(), vector.getY());
}


//void Shader::setUniformBaseLight(const uniformStruct &uniform, const BaseLight &light){
//    std::string lastName = uniform.name.substr(uniform.name.find_last_of('.')+1);
//    if(lastName == "color")setVec3(uniform.name, light.getColor());
//    if(lastName == "intensity")setFloat(uniform.name, light.getIntensity());
//}
//
//void Shader::setUniformDirectionalLight(const uniformStruct &uniform, const DirectionalLight &light){
//    std::string lastName = uniform.name.substr(uniform.name.find_last_of('.')+1);
//    setUniformBaseLight(uniform, light);
//    if(lastName == "direction")setVec3(uniform.name, light.getDirection());
//}
//
//
//void Shader::setUniformPointLight(const uniformStruct &uniform, const PointLight &light) {
//    std::string lastName = uniform.name.substr(uniform.name.find_last_of('.')+1);
//    setUniformBaseLight(uniform, light);
//    if(lastName == "position")setVec3(uniform.name, light.getTransform().getTransformedPos());
//    if(lastName == "constant")setFloat(uniform.name, light.getConstant());
//    if(lastName == "linear")setFloat(uniform.name, light.getLinear());
//    if(lastName == "quadratic")setFloat(uniform.name, light.getQuadratic());
//    if(lastName == "range")setFloat(uniform.name, light.getRange());
//}
//
//void Shader::setUniformSpotLight(const uniformStruct &uniform, const SpotLight &light) {
//    std::string lastName = uniform.name.substr(uniform.name.find_last_of('.')+1);
//    setUniformPointLight(uniform, light);
//    if(lastName == "direction")setVec3(uniform.name, light.getDirection());
//    if(lastName == "cutOff")setFloat(uniform.name, light.getCutoff());
//    if(lastName == "outerCutOff")setFloat(uniform.name, light.getOuterCutoff());
//}

//
//void Shader::updateUniforms(Transform &transform, const Material &material, RenderingEngine* renderingEngine) {
//
//    for(auto u : uniforms){
//        if(u.name.substr(0, 8) == "material"){
//            std::string lastName = u.name.substr(u.name.find_last_of('.')+1);
//            if(u.type == "sampler2D"){
//                //TODO: textureBinding
//                unsigned int samplerSlot = renderingEngine->getSamplerSlot(lastName);
//                material.getTexture(lastName)->bind(samplerSlot);
//
//                setInt(u.name, samplerSlot);
//            }
//            if(u.type == "float")
//                setFloat(u.name, material.getFloat(lastName));
//            if(u.type == "vec3")
//                setVec3(u.name, material.getVector3f(lastName));
//        } else if(u.type == "sampler2D"){
//            //TODO: textureBinding
//            unsigned int samplerSlot = renderingEngine->getSamplerSlot(u.name);
//            renderingEngine->getTexture(u.name)->bind(samplerSlot);
//
//            setInt(u.name, samplerSlot);
//        }
//        else if(u.name == "viewPos")
//            setVec3(u.name, renderingEngine->getMainCamera()->getTransform().getTransformedPos());
//        else if(u.name.substr(0, 8) == "dirLight")
//            setUniformDirectionalLight(u, *(DirectionalLight*)renderingEngine->getActiveLight());
//        else if(u.name.substr(0, 10) == "pointLight")
//            setUniformPointLight(u, *(PointLight*)renderingEngine->getActiveLight());
//        else if(u.name.substr(0, 9) == "spotLight")
//            setUniformSpotLight(u, *(SpotLight*)renderingEngine->getActiveLight());
//        else if(u.name == "MVP")
//            setMat4(u.name, transform.getProjectedTransformation(*renderingEngine->getMainCamera()));
//        else if(u.name == "worldMatrix")
//            setMat4(u.name, transform.getTransformation());
//        else if(u.name == "lightMatrix")
//            setMat4(u.name, renderingEngine->getLightMatrix() * transform.getTransformation());
//        else if(u.type == "float")
//            setFloat(u.name, renderingEngine->getFloat(u.name));
//        else if(u.type == "vec3")
//            setVec3(u.name, renderingEngine->getVector3f(u.name));
//    }
//
//
//}

unsigned int Shader::getProgram() const {
    return program;
}

void Shader::setProgram(unsigned int program) {
    Shader::program = program;
}
