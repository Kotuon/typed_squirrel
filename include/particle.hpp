
#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#pragma once

#include "math_types.hpp"

namespace SquirrelEngine {

struct Particle {
    Particle();

    void initialize( const vector3 t_pos = vector3( 0.f ),
                     const vector3 t_vel = vector3( 0.f ),
                     const vector3 t_accel = vector3( 0.f, -10.f, 0.f ),
                     const vector4 t_col = vector4( 1.f ), float t_life = 5.f,
                     bool t_isAlive = true );

    vector3 pos;
    vector3 vel;
    vector3 accel;

    vector4 col;

    float life;
    bool isAlive;
};

} // namespace SquirrelEngine

#endif
