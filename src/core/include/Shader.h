//
// Created by rostard on 14.12.17.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <vector>
#include "Vector2f.h"
#include "core_export.h"
class RenderingEngine;
class DirectionalLight;
class PointLight;
class SpotLight;

struct uniformStruct{
    std::string type;
    std::string name;
};

class CORE_EXPORT Shader {
public:
    Shader();

    Shader(const Shader& shader);

    void addVertexShader(const std::string& shaderSource);
    void addFragmentShader(const std::string& shaderSource);
    void addGeometryShader(const std::string& shaderSource);

    void linkProgram();

    void bind();

    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
//    void setMat4(const std::string &name, Matrix4f matrix) const;
    void setVec2(const std::string &name, Vector2f vector) const;
    void setVec3(const std::string &name, Vector3f vector) const;

//    virtual void updateUniforms(Transform &transform, const Material &material, RenderingEngine* renderingEngine);
    unsigned int getProgram() const;

    void setProgram(unsigned int program);
protected:

private:
//    void setUniformBaseLight(const uniformStruct &uniform, const BaseLight &light);
//    void setUniformDirectionalLight(const uniformStruct &uniform, const DirectionalLight &light);
//    void setUniformPointLight(const uniformStruct &uniform, const PointLight &light);
//    void setUniformSpotLight(const uniformStruct &uniform, const SpotLight &light);

    void addShader(const std::string& shaderSource, int shaderType);

    unsigned int program;

    std::vector<uniformStruct> uniforms;
};


#endif //ENGINE_SHADER_H
