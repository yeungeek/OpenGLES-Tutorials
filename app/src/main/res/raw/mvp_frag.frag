#version 300 es
precision mediump float;
in vec2 vTexCoord;
layout (location = 0) out vec4 vFragColor;
uniform sampler2D sTextureMap;

void main() {
    vFragColor = texture(sTextureMap, vTexCoord);
}