
#ifndef COMPUTE_TEST_HPP
#define COMPUTE_TEST_HPP
#pragma once

#include <array>

#include "math_types.hpp"
#include "shader.hpp"

namespace SquirrelEngine {

struct Particle {
    vector3 position;
    vector3 velocity;
    vector3 accel;
    vector4 color;
    float life;
};

struct ParticleEmitter {
    vector4 minColor, maxColor;
    vector3 minOffset, maxOffset;
    vector3 minVelocity, maxVelocity;
    vector3 minAccel, maxAccel;
    float minLife, maxLife;

    vector3 position;

    float spawnInterval, timer;
    uint32_t maxParticles;
    unsigned particlesBuffer;
    unsigned freelistBuffer;
    unsigned texture;
};

namespace Test {

class ParticlesTest {
public:
    ~ParticlesTest() = default;

    void init();
    void update( const float dt );

private:
    std::unique_ptr< ParticleEmitter > emitter;
    std::unique_ptr< Program > emitterShader;
    std::unique_ptr< Program > particleShader;

    static constexpr size_t maxParticles = 10;
    std::array< Particle, maxParticles > particles;
    std::array< int, maxParticles > freeList;
};

} // namespace Test
} // namespace SquirrelEngine

#endif
