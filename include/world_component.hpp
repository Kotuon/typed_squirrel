
#ifndef WORLD_COMPONENT_HPP
#define WORLD_COMPONENT_HPP
#pragma once

#include "component.hpp"
#include "transform.hpp"

namespace SquirrelEngine {
class Entity;

class WorldComponent : public Component {
public:
    WorldComponent( Entity* t_parent );

    virtual ~WorldComponent() = default;

    Transform* getLocalTransform();

    const vector3 forwardVector() const;

    const vector3 rightVector() const;

    const vector3 upVector() const;

protected:
    Transform m_localTransform;
};

} // namespace SquirrelEngine

#endif
