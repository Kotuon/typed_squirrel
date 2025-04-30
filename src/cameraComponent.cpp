
#include "cameraComponent.hpp"
#include "transform.hpp"

namespace SquirrelEngine {

CameraComponent::CameraComponent()
    : fov( 45.f ), fnear( 0.1f ), ffar( 1000.f ), aspect( 4.f / 3.f ),
      primary( true ), m_eulerRotation( 0.f ), m_rotationIsDirty( false ) {}

matrix4 CameraComponent::viewMatrix() {
    vector3 position = transform.getPosition();

    if ( m_rotationIsDirty ) {
        transform.setRotation( m_eulerRotation );
        m_rotationIsDirty = false;
    }

    vector3 fwd = transform.forwardVector();
    vector3 up = transform.upVector();

    return glm::lookAt( position, position + fwd, up );
    // return glm::lookAt( position, vector3( 0.f, 0.f, 0.f ), up );
}

matrix4 CameraComponent::projectionMatrix() {
    return glm::perspective< float >( glm::radians( fov ), aspect, fnear,
                                      ffar );
}

void CameraComponent::setPitch( const float angle ) {
    m_eulerRotation.x = angle;
    m_rotationIsDirty = true;
}

void CameraComponent::setYaw( const float angle ) {
    m_eulerRotation.y = angle;
    m_rotationIsDirty = true;
}

void CameraComponent::setRoll( const float angle ) {
    m_eulerRotation.z = angle;
    m_rotationIsDirty = true;
}

void CameraComponent::rotatePitch( const float angle ) {
    m_eulerRotation.x += angle;
    m_rotationIsDirty = true;
}

void CameraComponent::rotateYaw( const float angle ) {
    m_eulerRotation.y += angle;
    m_rotationIsDirty = true;
}

void CameraComponent::rotateRoll( const float angle ) {
    m_eulerRotation.z += angle;
    m_rotationIsDirty = true;
}

const vector3& CameraComponent::getEulerRotation() const {
    return m_eulerRotation;
}

const float CameraComponent::getSensitivity() const { return m_sensitivity; }

} // namespace SquirrelEngine
