
#ifndef LOCAL_TRANSFORM_HPP
#define LOCAL_TRANSFORM_HPP
#pragma once

#include "transform.hpp"

namespace SquirrelEngine {
class Entity;

class LocalTransform : private Transform {
public:
    void setOwner( Entity* t_owner );

    // Position
    void setWorldPosition( const vector3& t_position );
    void setLocalPosition( const vector3& t_position );

    const vector3 getWorldPosition() const;

    const vector3& getLocalPosition() const;
    vector3& getLocalPosition();

    // Scale
    void setWorldScale( const vector3& t_scale );
    void setLocalScale( const vector3& t_scale );

    const vector3 getWorldScale() const;

    const vector3& getLocalScale() const;
    vector3& getLocalScale();

    // Rotation
    void setWorldRotation( const quat& t_rotation );
    void setLocalRotation( const quat& t_rotation );

    const quat getWorldRotation() const;
    const quat& getLocalRotation() const;

    const vector3 getWorldEulerRotation() const;
    const vector3 getLocalEulerRotation() const;

    // Direction vectors
    const vector3 forwardVector() const;

    const vector3 rightVector() const;

    const vector3 upVector() const;

private:
    Entity* m_owner;
};

} // namespace SquirrelEngine

#endif
