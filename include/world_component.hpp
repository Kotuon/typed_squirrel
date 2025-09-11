
#ifndef WORLD_COMPONENT_HPP
#define WORLD_COMPONENT_HPP
#pragma once

#include "component.hpp"
#include "local_transform.hpp"

namespace SquirrelEngine {
class Entity;

class WorldComponent : public Component {
public:
    WorldComponent( Entity* t_parent );

    virtual ~WorldComponent() = default;

    LocalTransform* getLocalTransform();

    const vector3 forwardVector() const;

    const vector3 rightVector() const;

    const vector3 upVector() const;

protected:
    LocalTransform m_localTransform;
};

} // namespace SquirrelEngine

#endif
