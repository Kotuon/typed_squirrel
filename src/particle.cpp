
#include "particle.hpp"

namespace SquirrelEngine {

Particle::Particle()
    : pos( { 0.f } ), vel( { 0.f } ), accel( { 0.f, -10.f, 0.f } ),
      col( { 1.f } ), life( 5.f ), isAlive( false ) {}

} // namespace SquirrelEngine
