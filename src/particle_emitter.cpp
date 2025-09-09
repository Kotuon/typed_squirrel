
#include "entity.hpp"
#include "model.hpp"
#include "particle_emitter.hpp"
#include "particle.hpp"
#include "shader.hpp"

namespace SquirrelEngine {

ParticleEmitter::ParticleEmitter( Entity* t_parent )
    : WorldComponent( t_parent ) {}

ParticleEmitter::~ParticleEmitter() {}

void ParticleEmitter::initialize() {
    // Create model object
    particleModel = std::make_unique< Model >( nullptr );
    // Load model and shader
    particleModel->initMesh( "models/sphere.obj" );
    particleModel->initShader( "shaders/instance.vert",
                               "shaders/instance.frag" );
    // Enable instanced buffers
    particleModel->enableInstanced();

    for ( uint64_t i = 0; i < MaxParticles; ++i ) {
        particleList[i] = std::make_unique< Particle >();
    }
}

void ParticleEmitter::update( const float dt ) {
    // If should make new particle.
    // Make new particle if open space in list
    timer += dt;
    if ( timer >= spawnInterval && particleCount < MaxParticles ) {
        timer = 0.f;

        Particle* newParticle = particleList[particleCount].get();

        newParticle->pos =
            owner->transform.getPosition() + m_localTransform.getPosition();
        newParticle->vel = vector3{ 0.f, 10.f, 0.f };
        newParticle->isAlive = true;

        particleCount += 1;
    }

    // If there are more than 0 particles
    if ( particleCount <= 0 ) return; // Early exit

    int posCounter = 0;
    int colCounter = 0;

    for ( int i = 0; i < particleCount; ++i ) {
        Particle* p = particleList[i].get();

        if ( !p->isAlive ) continue;

        // Update particle objects
        p->vel += p->accel * dt;
        p->pos += p->vel * dt;

        p->life -= dt;
        if ( p->life <= 0.f ) {
            p->isAlive = false;
            std::swap( particleList[i], particleList[particleCount - 1] );
            i -= 1;
            continue;
        }

        // Add values to arrays
        particlePos[posCounter++] = p->pos.x;
        particlePos[posCounter++] = p->pos.y;
        particlePos[posCounter++] = p->pos.z;
        particlePos[posCounter++] = 0.f;

        particleCol[colCounter++] = p->col.r;
        particleCol[colCounter++] = p->col.g;
        particleCol[colCounter++] = p->col.b;
        particleCol[colCounter++] = p->col.a;
    }

    // Send values to shader
    particleModel->bindInstanced( particlePos.data(), particleCol.data(),
                                  particleCount );
}

void ParticleEmitter::render() {
    // Draw particles
    particleModel->drawInstanced( particleCount );
}

} // namespace SquirrelEngine
