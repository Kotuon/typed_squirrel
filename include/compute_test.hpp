
#ifndef COMPUTE_TEST_HPP
#define COMPUTE_TEST_HPP
#pragma once

#include <array>

#include "math_types.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace SquirrelEngine {

namespace Test {

struct Particle {
    vector3 pos{ 0.f, 0.f, 0.f }, vel{ 0.f, 100.f, 0.f };
    vector4 col{ 1.f, 0.f, 0.f, 1.f };
    float life;
};

class ParticlesTest {
public:
    ~ParticlesTest() = default;

    void init();
    void update( const float dt );
    void render();

private:
    static inline const GLfloat vertexData[] = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f,  0.0f, 0.5f, 0.5f,  0.0f,
    };

    static constexpr uint64_t MaxParticles = 64;

    std::array< std::unique_ptr< Particle >, MaxParticles > particleList{
        nullptr };

    std::array< GLfloat, MaxParticles * 4 > particlePos;
    std::array< GLfloat, MaxParticles * 4 > particleCol;

    uint64_t ParticleCount = 10;

    std::unique_ptr< Model > particleModel;
};

} // namespace Test
} // namespace SquirrelEngine

#endif
