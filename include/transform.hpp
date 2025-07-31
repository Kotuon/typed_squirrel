/**
 *
 * @file transform.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Transform class, which handles position, rotation, and
 * scale for objects in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#pragma once

#include "math_types.hpp"
#include "object.hpp"
#include "dual_quaternion.hpp"

namespace SquirrelEngine {

/**
 * @brief Represents a transform with position, rotation, and scale.
 */
class Transform : public Object {
public:
    /**
     * @brief Default constructor for Transform.
     */
    Transform();

    /**
     * @brief Virtual destructor for Transform.
     */
    ~Transform() = default;

    /**
     * @brief Sets the position of the transform.
     * @param t_position The new position.
     */
    void setPosition( const vector3& t_position );

    /**
     * @brief Gets the position of the transform.
     * @return The current position.
     */
    const vector3 getPosition() const;

    /**
     * @brief Sets the scale of the transform.
     * @param t_scale The new scale.
     */
    void setScale( const vector3& t_scale );

    /**
     * @brief Gets the scale of the transform.
     * @return The current scale.
     */
    const vector3& getScale() const;

    /**
     * @brief Sets the rotation of the transform.
     * @param t_rotation The new rotation as a quaternion.
     */
    void setRotation( const Quaternion& t_rotation );

    /**
     * @brief Gets the rotation of the transform.
     * @return The current rotation as a quaternion.
     */
    const Quaternion& getRotation() const;

    /**
     * @brief Gets the rotation of the transform as Euler angles.
     * @return The current rotation as Euler angles.
     */
    const vector3 getEulerRotation() const;

    /**
     * @brief Moves the transform by a given amount.
     * @param amount The amount to move.
     */
    void move( const vector3& amount );

    /**
     * @brief Rotates the transform by a quaternion.
     * @param rotation The rotation quaternion.
     */
    void rotate( const Quaternion& rotation );

    /**
     * @brief Rotates the transform around an axis by an angle.
     * @param axis The axis to rotate around.
     * @param angle The angle in radians.
     */
    void rotate( const vector3& axis, const float angle );

    /**
     * @brief Scales the transform by a factor.
     * @param factor The scale factor.
     */
    void scale( const float factor );

    /**
     * @brief Gets the forward direction vector.
     * @return The forward vector.
     */
    const vector3 forwardVector() const;

    /**
     * @brief Gets the right direction vector.
     * @return The right vector.
     */
    const vector3 rightVector() const;

    /**
     * @brief Gets the up direction vector.
     * @return The up vector.
     */
    const vector3 upVector() const;

    /**
     * @brief Rotates the transform to look in a given direction.
     * @param direction The direction to look.
     */
    void look( const vector3& direction );

    /**
     * @brief Gets the transformation matrix.
     * @return The transformation matrix.
     */
    const matrix4& matrix();

private:
    matrix4 m_matrix;           //!< Cached transformation matrix.
    DualQuaternion m_transform; //!< dual quaternion for position and rotation
    vector3 m_scale;            //!< Scale vector.
    bool m_isDirty;             //!< Dirty flag for matrix recalculation.
};

} // namespace SquirrelEngine

#endif