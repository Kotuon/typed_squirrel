
#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP
#pragma once

#include "component.hpp"
#include "transform.hpp"
#include "math_types.hpp"

namespace SquirrelEngine {
class Transform;
class DataRecord;

class CameraComponent : public Component {
public:
    CameraComponent( Entity* t_parent );
    ~CameraComponent() = default;

    matrix4 viewMatrix();
    matrix4 projectionMatrix();

    void serializeComponent( DataRecord* record );
    void deserializeComponent( DataRecord* record );

    void setPitch( const float angle );
    void setYaw( const float angle );
    void setRoll( const float angle );

    void rotatePitch( const float angle );
    void rotateYaw( const float angle );
    void rotateRoll( const float angle );

    const vector3& getEulerRotation() const;

    const float getSensitivity() const;
    void setSensitivity( const float sensitivity );

    Transform transform;

    float fov;

    float fnear;
    float ffar;

    float aspect;

    bool primary;

protected:
    vector3 m_eulerRotation;
    float m_sensitivity = 1.f;
    bool m_rotationIsDirty;
};

} // namespace SquirrelEngine

#endif
