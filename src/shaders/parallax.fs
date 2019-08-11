#version 330 core

in vec2 texCoords0;

uniform float offset;
uniform sampler2D image;

void main(){
    vec4 texColor = texture(image, texCoords0 + vec2(offset, 0)).rgba;
    gl_FragColor = vec4(texColor);
}