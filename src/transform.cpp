
#include "transform.hpp"

namespace SquirrelEngine {

Transform::Transform()
    : m_position( 0.f ), m_scale( 1.f ), m_rotation( 1.f, 0.f, 0.f, 0.f ),
      m_isDirty( true ) {}

// Position functions
void Transform::setPosition( const vector3& t_position ) {
    m_position = t_position;
    m_isDirty = true;
}

const vector3& Transform::getPosition() const { return m_position; }

void Transform::move( const vector3& amount ) {
    m_position += amount;
    m_isDirty = true;
}

// Scale functions
void Transform::setScale( const vector3& t_scale ) {
    m_scale = t_scale;
    m_isDirty = true;
}

const vector3& Transform::getScale() const { return m_scale; }

void Transform::scale( const float factor ) {
    m_scale *= factor;
    m_isDirty = true;
}

// Rotation functions
void Transform::setRotation( const quat& t_rotation ) {
    m_rotation = t_rotation;
    m_isDirty = true;
}

const quat& Transform::getRotation() const { return m_rotation; }

void Transform::rotate( const quat& rotation ) {
    m_rotation *= rotation;
    m_isDirty = true;
}

void Transform::rotate( const vector3& axis, const float angle ) {
    quat newRotation = glm::angleAxis( angle, axis );
    m_rotation = m_rotation * newRotation;
    m_isDirty = true;
}

// Direction vectors
const vector3 Transform::forwardVector() const {
    return m_rotation * vector3( 0.f, 0.f, -1.f );
}

const vector3 Transform::rightVector() const {
    return m_rotation * vector3( 0.f, 1.f, 0.f );
}

const vector3 Transform::upVector() const {
    return m_rotation * vector3( 1.f, 0.f, 0.f );
}

void Transform::look( const vector3& direction ) {
    const float dot = glm::dot( vector3( 0.f, 0.f, -1.f ), direction );
    if ( dot > 0.999999f || dot < -0.999999f ) {
        m_rotation = quat( 0.f, 0.f, 0.f, 1.f );
        return;
    }

    vector3 a = glm::cross( vector3( 0.f, 0.f, -1.f ), direction );
    float directionLength = glm::length( direction );
    float w = directionLength + dot;

    m_rotation = { a.x, a.y, a.z, w };
}

const matrix4& Transform::matrix() {
    if ( m_isDirty ) {
        const matrix4 t = glm::translate( matrix4( 1.f ), m_position );
        const matrix4 s = glm::scale( matrix4( 1.f ), m_scale );
        const matrix4 r = glm::toMat4( m_rotation );

        m_matrix = t * r * s;

        m_isDirty = false;
    }

    return m_matrix;
}

} // namespace SquirrelEngine
