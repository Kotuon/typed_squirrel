
#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP
#pragma once

#include <array>

#include <glad/glad.h>

#include "math_types.hpp"
#include "world_component.hpp"

namespace SquirrelEngine {
class Entity;
class Model;
struct Particle;

class ParticleEmitter : public WorldComponent {
public:
    ParticleEmitter( Entity* t_parent );

    ~ParticleEmitter();

    void initialize();
    void update( const float dt );
    void render();

protected:
    vector3 minVelocity, maxVelocity;
    vector3 minOffset, maxOffset;
    float minLife, maxLife;

    float spawnInterval = 1.f;
    float timer = 0.f;

private:
    static constexpr uint64_t MaxParticles = 64;

    std::array< std::unique_ptr< Particle >, MaxParticles > particleList{
        nullptr };

    std::array< GLfloat, MaxParticles * 4 > particlePos;
    std::array< GLfloat, MaxParticles * 4 > particleCol;

    std::unique_ptr< Model > particleModel;

    uint64_t particleCount = 0;
};

} // namespace SquirrelEngine

#endif
