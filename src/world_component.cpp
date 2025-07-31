
#include "entity.hpp"
#include "world_component.hpp"

namespace SquirrelEngine {

WorldComponent::WorldComponent( Entity* t_parent ) : Component( t_parent ) {}

Transform* WorldComponent::getLocalTransform() { return &m_localTransform; }

const vector3 WorldComponent::forwardVector() const {
    Quaternion q =
        m_localTransform.getRotation() * owner->transform.getRotation();

    return q * vector3( 0.f, 0.f, -1.f );
}

const vector3 WorldComponent::rightVector() const {
    Quaternion q =
        m_localTransform.getRotation() * owner->transform.getRotation();

    return q * vector3( 1.f, 0.f, 0.f );
}

const vector3 WorldComponent::upVector() const {
    Quaternion q =
        m_localTransform.getRotation() * owner->transform.getRotation();

    return q * vector3( 0.f, 1.f, 0.f );
}

} // namespace SquirrelEngine
