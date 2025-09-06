
#include <memory>

#include "compute_test.hpp"

namespace SquirrelEngine {
namespace Test {

void ParticlesTest::init() {
    emitter = std::make_unique< ParticleEmitter >(
        vector4( 1.f, 1.f, 1.f, 1.f ), vector4( 1.f, 1.f, 1.f, 1.f ),
        vector3( 0.f, 0.f, 0.f ), vector3( 0.f, 0.f, 0.f ),
        vector3( -10.f, -10.f, -10.f ), vector3( 10.f, 10.f, 10.f ),
        vector3( 0.f, 0.f, 0.f ), vector3( 0.f, 0.f, 0.f ), 1000.f, 1000.f,
        vector3( 0.f, 0.f, 0.f ), 2.f, 0.f, 1000, 0, 0, 0 );

    emitterShader = std::make_unique< Program >(
        new Program{ "shaders/particleEmitter.comp" } );

    particleShader = std::make_unique< Program >(
        new Program{ "shaders/particle.vert", "shaders/particle.comp",
                     "shaders/particle.frag" } );

    // glCreateBuffers( 1, &emitter->particlesBuffer );
    // glCreateBuffers( 1, &emitter->freelistBuffer );

    glGenBuffers( 1, &emitter->particlesBuffer );
    glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->particlesBuffer );
    glBufferData( GL_SHADER_STORAGE_BUFFER, maxParticles * sizeof( Particle ),
                  particles.data(), GL_DYNAMIC_COPY );

    glGenBuffers( 1, &emitter->freelistBuffer );
    glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->freelistBuffer );
    glBufferData( GL_SHADER_STORAGE_BUFFER, maxParticles * sizeof( int ),
                  freeList.data(), GL_DYNAMIC_COPY );

    glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );
}

void ParticlesTest::update( const float dt ) {
    glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
    emitterShader->use();
    // for ( auto& emitter : emitters ) {
    emitter->timer += dt;

    unsigned particlesToSpawn =
        static_cast< unsigned >( emitter->timer / emitter->spawnInterval );
    emitter->timer = fmodf( emitter->timer, emitter->spawnInterval );

    if ( particlesToSpawn > 0 ) {
        // SetParticleSpawnUniforms
        // emitter->particlesBuffer.bindSSBO(0);
        glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->particlesBuffer );
        glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0,
                          emitter->particlesBuffer );
        // emitter->freelistBuffer.bindSSBO(1);
        glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->freelistBuffer );
        glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 1,
                          emitter->freelistBuffer );

        int workGroupSize =
            64; // QueryLinearWorkGroupSize(particleEmitterShader);
        int numWorkGroups =
            ( particlesToSpawn + workGroupSize - 1 ) / workGroupSize;
        glDispatchCompute( numWorkGroups, 1, 1 );
    }
    // }
    glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );

    particleShader->use();
    particleShader->setFloat( "dt", dt );
    // for ( auto& emitter : emitters ) {
    // emitter->particlesBuffer.bindSSBO(0);
    glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->particlesBuffer );
    glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0, emitter->particlesBuffer );
    // emitter->freelistBuffer.bindSSBO(1);
    glBindBuffer( GL_SHADER_STORAGE_BUFFER, emitter->freelistBuffer );
    glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 1, emitter->freelistBuffer );

    int workGroupSize = 128; // QueryLinearWorkGroupSize(particleEmitterShader);
    int numWorkGroups =
        ( particlesToSpawn + workGroupSize - 1 ) / workGroupSize;
    glDispatchCompute( numWorkGroups, 1, 1 );
}

} // namespace Test
} // namespace SquirrelEngine
