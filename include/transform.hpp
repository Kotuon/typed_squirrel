
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#pragma once

#include "math_types.hpp"
#include "object.hpp"

namespace SquirrelEngine {

class Transform : public Object {
public:
    Transform();
    ~Transform() = default;

    void setPosition( const vector3& t_position );
    const vector3& getPosition() const;

    void setScale( const vector3& t_scale );
    const vector3& getScale() const;

    void setRotation( const quat& t_rotation );
    const quat& getRotation() const;

    void move( const vector3& amount );

    void rotate( const quat& rotation );
    void rotate( const vector3& axis, const float angle );

    void scale( const float factor );

    const vector3 forwardVector() const;
    const vector3 rightVector() const;
    const vector3 upVector() const;

    void look( const vector3& direction );

    const matrix4& matrix();

private:
    matrix4 m_matrix;

    vector3 m_position;
    vector3 m_scale;
    quat m_rotation;

    bool m_isDirty;
};

} // namespace SquirrelEngine

#endif
