/**
 *
 * @file cameraComponent.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the CameraComponent class, which provides camera
 * functionality for entities in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "cameraComponent.hpp"
#include "entity.hpp"
#include "transform.hpp"

namespace SquirrelEngine {

/**
 * @brief Constructs a CameraComponent with the given parent entity.
 * @param t_parent Pointer to the parent Entity.
 */
CameraComponent::CameraComponent( Entity* t_parent )
    : WorldComponent( t_parent ), fov( 45.f ), fnear( 0.1f ), ffar( 1000.f ),
      aspect( 4.f / 3.f ), primary( true ), m_eulerRotation( 0.f ),
      m_rotationIsDirty( false ) {}

/**
 * @brief Calculates and returns the view matrix for the camera.
 * @return The view matrix as a matrix4.
 */
matrix4 CameraComponent::viewMatrix() {
    vector3 position =
        owner->transform.getPosition() + m_localTransform.getPosition();

    if ( m_rotationIsDirty ) {
        m_localTransform.setRotation( Quaternion::fromEuler(
            m_eulerRotation.x, m_eulerRotation.y, m_eulerRotation.z ) );
        m_rotationIsDirty = false;
    }

    vector3 fwd = forwardVector();
    vector3 up = upVector();

    return glm::lookAt( position, position + fwd, up );
}

/**
 * @brief Calculates and returns the projection matrix for the camera.
 * @return The projection matrix as a matrix4.
 */
matrix4 CameraComponent::projectionMatrix() {
    return glm::perspective< float >( glm::radians( fov ), aspect, fnear,
                                      ffar );
}

/**
 * @brief Sets the camera's pitch (rotation around the X axis).
 * @param angle The pitch angle in degrees or radians.
 */
void CameraComponent::setPitch( const float angle ) {
    m_eulerRotation.x = angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Sets the camera's yaw (rotation around the Y axis).
 * @param angle The yaw angle in degrees or radians.
 */
void CameraComponent::setYaw( const float angle ) {
    m_eulerRotation.y = angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Sets the camera's roll (rotation around the Z axis).
 * @param angle The roll angle in degrees or radians.
 */
void CameraComponent::setRoll( const float angle ) {
    m_eulerRotation.z = angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Adds to the camera's pitch (rotation around the X axis).
 * @param angle The amount to add to the pitch.
 */
void CameraComponent::addPitch( const float angle ) {
    m_eulerRotation.x += angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Adds to the camera's yaw (rotation around the Y axis).
 * @param angle The amount to add to the yaw.
 */
void CameraComponent::addYaw( const float angle ) {
    m_eulerRotation.y += angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Adds to the camera's roll (rotation around the Z axis).
 * @param angle The amount to add to the roll.
 */
void CameraComponent::addRoll( const float angle ) {
    m_eulerRotation.z += angle;
    m_rotationIsDirty = true;
}

/**
 * @brief Gets the camera's Euler rotation as a vector.
 * @return Reference to the vector3 representing Euler rotation.
 */
const vector3& CameraComponent::getEulerRotation() const {
    return m_eulerRotation;
}

/**
 * @brief Gets the camera's sensitivity value.
 * @return The sensitivity as a float.
 */
const float CameraComponent::getSensitivity() const { return m_sensitivity; }

/**
 * @brief Sets the camera's sensitivity value.
 * @param sensitivity The new sensitivity value.
 */
void CameraComponent::setSensitivity( const float sensitivity ) {
    m_sensitivity = sensitivity;
}

} // namespace SquirrelEngine
