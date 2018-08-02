#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texCoords;

out vec2 texCoords0;

uniform vec2 size;
uniform vec2 position;
uniform vec2 screenSize;

void main(){
    texCoords0 = texCoords;
    gl_Position = vec4((position + pos * size) / screenSize - 1.0, 0.0, 1.0);
}