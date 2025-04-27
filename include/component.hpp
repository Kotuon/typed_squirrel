
#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {
class Entity;

class Component : public Object {
public:
    Component();
    virtual ~Component() = default;

    Entity* parent;
};

} // namespace SquirrelEngine

#endif
