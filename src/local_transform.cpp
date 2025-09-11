
#include "entity.hpp"
#include "local_transform.hpp"

namespace SquirrelEngine {

void LocalTransform::setOwner( Entity* t_owner ) { m_owner = t_owner; }

// Position
void LocalTransform::setWorldPosition( const vector3& t_position ) {
    setPosition( t_position - m_owner->transform.getPosition() );
}
void LocalTransform::setLocalPosition( const vector3& t_position ) {
    setPosition( t_position );
}

const vector3 LocalTransform::getWorldPosition() const {
    return m_owner->transform.getPosition() + m_position;
}

const vector3& LocalTransform::getLocalPosition() const {
    return getPosition();
}
vector3& LocalTransform::getLocalPosition() { return getPosition(); }

// Scale
void LocalTransform::setWorldScale( const vector3& t_scale ) {
    setScale( t_scale - m_owner->transform.getScale() );
}
void LocalTransform::setLocalScale( const vector3& t_scale ) {
    setScale( t_scale );
}

const vector3 LocalTransform::getWorldScale() const {
    return m_owner->transform.getScale() + m_scale;
}

const vector3& LocalTransform::getLocalScale() const { return getScale(); }
vector3& LocalTransform::getLocalScale() { return getScale(); }

// Rotation
void LocalTransform::setWorldRotation( const quat& t_rotation ) {
    // TODO: fix this
    setRotation( t_rotation *
                 glm::conjugate( m_owner->transform.getRotation() ) );
}
void LocalTransform::setLocalRotation( const quat& t_rotation ) {
    setRotation( t_rotation );
}

const quat LocalTransform::getWorldRotation() const {
    return m_rotation * m_owner->transform.getRotation();
}
const quat& LocalTransform::getLocalRotation() const { return getRotation(); }

const vector3 LocalTransform::getWorldEulerRotation() const {
    return m_owner->transform.getEulerRotation() + getEulerRotation();
}
const vector3 LocalTransform::getLocalEulerRotation() const {
    return getEulerRotation();
}

// Direction vectors
const vector3 LocalTransform::forwardVector() const {
    return getWorldRotation() * vector3( 0.f, 0.f, -1.f );
}

const vector3 LocalTransform::rightVector() const {
    return getWorldRotation() * vector3( 1.f, 0.f, 0.f );
}

const vector3 LocalTransform::upVector() const {
    return getWorldRotation() * vector3( 0.f, 1.f, 0.f );
}

} // namespace SquirrelEngine
