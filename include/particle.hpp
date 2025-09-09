
#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#pragma once

#include "math_types.hpp"

namespace SquirrelEngine {

struct Particle {
    Particle();

    vector3 pos;
    vector3 vel;
    vector3 accel;
    
    vector4 col;

    float life;
    bool isAlive;
};

} // namespace SquirrelEngine

#endif
