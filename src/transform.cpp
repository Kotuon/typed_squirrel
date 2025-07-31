/**
 *
 * @file transform.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Transform class, which handles position, rotation, and
 * scale for objects in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "transform.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for Transform.
 */
Transform::Transform() : m_transform(), m_scale( 1.f ), m_isDirty( true ) {}

// Position functions

/**
 * @brief Sets the position of the transform.
 * @param t_position The new position.
 */
void Transform::setPosition( const vector3& t_position ) {
    m_transform.setTranslation( t_position );
    m_isDirty = true;
}

/**
 * @brief Gets the position of the transform.
 * @return The current position.
 */
const vector3 Transform::getPosition() const {
    return m_transform.getTranslation();
}

/**
 * @brief Moves the transform by a given amount.
 * @param amount The amount to move.
 */
void Transform::move( const vector3& amount ) {
    m_transform.addTranslation( amount );
    m_isDirty = true;
}

// Scale functions

/**
 * @brief Sets the scale of the transform.
 * @param t_scale The new scale.
 */
void Transform::setScale( const vector3& t_scale ) {
    m_scale = t_scale;
    m_isDirty = true;
}

/**
 * @brief Gets the scale of the transform.
 * @return The current scale.
 */
const vector3& Transform::getScale() const { return m_scale; }

/**
 * @brief Scales the transform by a factor.
 * @param factor The scale factor.
 */
void Transform::scale( const float factor ) {
    m_scale *= factor;
    m_isDirty = true;
}

// Rotation functions

/**
 * @brief Sets the rotation of the transform.
 * @param t_rotation The new rotation as a quaternion.
 */
void Transform::setRotation( const Quaternion& t_rotation ) {
    m_transform.setRotation( t_rotation );
    m_isDirty = true;
}

/**
 * @brief Gets the rotation of the transform.
 * @return The current rotation as a quaternion.
 */
const Quaternion& Transform::getRotation() const {
    return m_transform.getRotation();
}

/**
 * @brief Gets the rotation of the transform as Euler angles.
 * @return The current rotation as Euler angles.
 */
const vector3 Transform::getEulerRotation() const {
    return m_transform.getEulerRotation();
}

/**
 * @brief Rotates the transform by a quaternion.
 * @param rotation The rotation quaternion.
 */
void Transform::rotate( const Quaternion& rotation ) {
    m_transform.addRotation( rotation );
    m_isDirty = true;
}

/**
 * @brief Rotates the transform around an axis by an angle.
 * @param axis The axis to rotate around.
 * @param angle The angle in degrees.
 */
void Transform::rotate( const vector3& axis, const float angle ) {
    Quaternion newRotation = Quaternion::fromAxisAngle( axis.x, axis.y, axis.z,
                                                        glm::radians( angle ) );
    rotate( newRotation );
}

// Direction vectors

/**
 * @brief Gets the forward direction vector.
 * @return The forward vector.
 */
const vector3 Transform::forwardVector() const {
    return m_transform.getRotation() * vector3( 0.f, 0.f, -1.f );
}

/**
 * @brief Gets the right direction vector.
 * @return The right vector.
 */
const vector3 Transform::rightVector() const {
    return m_transform.getRotation() * vector3( 1.f, 0.f, 0.f );
}

/**
 * @brief Gets the up direction vector.
 * @return The up vector.
 */
const vector3 Transform::upVector() const {
    return m_transform.getRotation() * vector3( 0.f, 1.f, 0.f );
}

/**
 * @brief Rotates the transform to look in a given direction.
 * @param direction The direction to look.
 */
void Transform::look( const vector3& direction ) {
    const float dot = glm::dot( vector3( 0.f, 0.f, -1.f ), direction );
    if ( dot > 0.999999f || dot < -0.999999f ) {
        m_transform.setRotation( Quaternion( 0.f, 0.f, 0.f, 1.f ) );
        return;
    }

    vector3 a = glm::cross( vector3( 0.f, 0.f, -1.f ), direction );
    float directionLength = glm::length( direction );
    float w = directionLength + dot;

    m_transform.setRotation( { a.x, a.y, a.z, w } );
}

/**
 * @brief Gets the transformation matrix.
 * @return The transformation matrix.
 */
const matrix4& Transform::matrix() {
    if ( m_isDirty ) {
        // const matrix4 t =
        //     glm::translate( matrix4( 1.f ), m_transform.getTranslation() );
        const matrix4 s = glm::scale( matrix4( 1.f ), m_scale );
        const matrix4 r = m_transform.getMatrix();

        m_matrix = r * s;

        m_isDirty = false;
    }

    return m_matrix;
}

} // namespace SquirrelEngine
