#version 300 es

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uMVPMatrix;
out vec2 vTexCoord;

void main() {
    gl_Position = uMVPMatrix * aPos;
    vTexCoord = aTexCoord;
}