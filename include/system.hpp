
#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {

class System : Object {
public:
    System() = default;
    virtual ~System() = default;

    virtual void initialize() {}
    virtual void update( float delta ) {}
    virtual void shutdown() {}
};

} // namespace SquirrelEngine

#endif
