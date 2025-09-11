
#include "entity.hpp"
#include "world_component.hpp"

namespace SquirrelEngine {

WorldComponent::WorldComponent( Entity* t_parent ) : Component( t_parent ) {
    m_localTransform.setOwner( t_parent );
}

LocalTransform* WorldComponent::getLocalTransform() {
    return &m_localTransform;
}

const vector3 WorldComponent::forwardVector() const {
    // quat q = m_localTransform.getRotation() * owner->transform.getRotation();

    // return q * vector3( 0.f, 0.f, -1.f );

    return m_localTransform.forwardVector();
}

const vector3 WorldComponent::rightVector() const {
    // quat q = m_localTransform.getRotation() * owner->transform.getRotation();

    // return q * vector3( 1.f, 0.f, 0.f );

    return m_localTransform.rightVector();
}

const vector3 WorldComponent::upVector() const {
    // quat q = m_localTransform.getRotation() * owner->transform.getRotation();

    // return q * vector3( 0.f, 1.f, 0.f );

    return m_localTransform.upVector();
}

} // namespace SquirrelEngine
