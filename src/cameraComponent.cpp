
#include "cameraComponent.hpp"
#include "transform.hpp"

namespace SquirrelEngine {

CameraComponent::CameraComponent()
    : fov( 45.f ), fnear( 0.1f ), ffar( 1000.f ), aspect( 4.f / 3.f ),
      primary( true ) {}

matrix4 CameraComponent::viewMatrix() {
    vector3 position = transform.getPosition();

    vector3 fwd = transform.forwardVector();
    vector3 up = transform.upVector();

    return glm::lookAt( position, position + fwd, up );
    // return glm::lookAt( position, vector3( 0.f, 0.f, 0.f ), up );
}

matrix4 CameraComponent::projectionMatrix() {
    return glm::perspective< float >( glm::radians( fov ), aspect, fnear,
                                      ffar );
}

} // namespace SquirrelEngine
