
#include "particle.hpp"

namespace SquirrelEngine {

Particle::Particle()
    : pos( vector3( 0.f ) ), vel( vector3( 0.f ) ),
      accel( vector3( 0.f, -10.f, 0.f ) ), col( vector4( 1.f ) ), life( 5.f ),
      isAlive( false ) {}

void Particle::initialize( const vector3 t_pos, const vector3 t_vel,
                           const vector3 t_accel, const vector4 t_col,
                           float t_life, bool t_isAlive ) {
    pos = t_pos;
    vel = t_vel;
    accel = t_accel;
    col = t_col;
    life = t_life;
    isAlive = t_isAlive;
}

} // namespace SquirrelEngine
