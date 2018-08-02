
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform vec2 WindowSize;

void main()
{
    gl_Position = vec4(2.0 * vertex.xy / WindowSize - 1.0, 0.0, 1.0);
    TexCoords = vertex.zw;
}
