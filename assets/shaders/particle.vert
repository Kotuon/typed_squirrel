#version 430 core

struct Particle {
    vec3 position;
    vec3 velocity;
    vec3 accel;
    vec4 color;
    float life;
};

layout(std430, binding = 0) readonly restrict buffer Particles {
    Particle particles[];
};

layout(location = 0) in vec2 aPos;

layout(location = 0) uniform mat4 view;
layout(location = 1) uniform vec3 right;
layout(location = 2) uniform vec3 up;

layout(location = 0) out vec2 texCoord;
layout(location = 1) out vec4 color;

void main() {
    texCoord = aPos + 0.5;

    int index = gl_InstanceID;

    Particle particle = particles[index];

    vec3 vPosWorld = particle.position.xyz + right * aPos.x +
        up * aPos.y;

    gl_Position = view * vec4(vPosWorld, 1.0);
}
