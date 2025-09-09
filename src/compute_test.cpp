
#include <memory>

#include "compute_test.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "cameraComponent.hpp"

namespace SquirrelEngine {
namespace Test {

void ParticlesTest::init() {
    particleModel = std::make_unique< Model >( nullptr );
    particleModel->initMesh( "models/sphere.obj" );
    particleModel->initShader( "shaders/instance.vert",
                               "shaders/instance.frag" );
    particleModel->enableInstanced();

    for ( uint64_t i = 0; i < MaxParticles; ++i ) {
        if ( !particleList[i] )
            particleList[i] = std::make_unique< Particle >();

        particleList[i]->pos = vector3{ 2.f * i, 0.f, 0.f };
    }
}

void ParticlesTest::update( const float dt ) {
    if ( ParticleCount <= 0 ) return;

    int posCounter = 0;
    int colCounter = 0;

    for ( uint64_t i = 0; i < ParticleCount; ++i ) {
        Particle* p = particleList[i].get();

        vector3 start{ 2.f * i, 0.f, 0.f };

        p->pos += p->vel * dt;
        if ( glm::distance( start, p->pos ) > 10.f )
            p->vel = ( start - p->pos );

        particlePos[posCounter++] = p->pos.x;
        particlePos[posCounter++] = p->pos.y;
        particlePos[posCounter++] = p->pos.z;
        particlePos[posCounter++] = 0.f;

        particleCol[colCounter++] = p->col.r;
        particleCol[colCounter++] = p->col.g;
        particleCol[colCounter++] = p->col.b;
        particleCol[colCounter++] = p->col.a;
    }

    particleModel->bindInstanced( particlePos.data(), particleCol.data(),
                                  ParticleCount );
}

void ParticlesTest::render() { particleModel->drawInstanced( ParticleCount ); }

} // namespace Test
} // namespace SquirrelEngine
