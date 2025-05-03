#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#pragma once

#include "error_codes.hpp"
#include "object.hpp"

namespace SquirrelEngine {
class Engine;

class System : public Object {
public:
    System() = default;
    virtual ~System() = default;

    virtual StartupErrors initialize( Engine* t_owner );
    virtual void update( const float ) {}
    virtual void shutdown() {}

protected:
    Engine* owner;
};

} // namespace SquirrelEngine

#endif
