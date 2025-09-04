#version 430 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec4 color;

layout(binding = 0) uniform sampler2D sprite;

layout(location = 0) out vec4 fragColor;

void main() {
    fragColor = texture(sprite, texCoord) * color;
}
