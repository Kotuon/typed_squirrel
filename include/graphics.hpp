
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#pragma once

#include "system.hpp"

namespace SquirrelEngine {
class Engine;

class Graphics : public System {
public:
    Graphics( Engine* t_engine );
    virtual ~Graphics();

    static SystemType getType();

private:
};

} // namespace SquirrelEngine

#endif
