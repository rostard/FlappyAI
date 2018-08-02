#version 330 core

in vec2 texCoords0;

uniform sampler2D image;

void main(){
    vec4 texColor = texture(image, texCoords0).rgba;
    gl_FragColor = vec4(texColor);
}