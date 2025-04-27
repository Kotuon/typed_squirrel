
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
    CameraComponent();
    ~CameraComponent() = default;

    matrix4 viewMatrix();
    matrix4 projectionMatrix();

    void serializeComponent( DataRecord* record );
    void deserializeComponent(DataRecord* record);

    Transform transform;

    float fov;

    float fnear;
    float ffar;

    float aspect;

    bool primary;

public:
};

} // namespace SquirrelEngine

#endif
