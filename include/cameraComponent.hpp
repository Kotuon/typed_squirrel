/**
 *
 * @file cameraComponent.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the CameraComponent class, which provides camera
 * functionality for entities in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP
#pragma once

#include "world_component.hpp"
#include "math_types.hpp"

namespace SquirrelEngine {
class DataRecord;

class CameraComponent : public WorldComponent {
public:
    /**
     * @brief Constructs a CameraComponent with the given parent entity.
     * @param t_parent Pointer to the parent Entity.
     */
    CameraComponent( Entity* t_parent );

    /**
     * @brief Default destructor.
     */
    ~CameraComponent() = default;

    /**
     * @brief Calculates and returns the view matrix for the camera.
     * @return The view matrix as a matrix4.
     */
    matrix4 viewMatrix();

    /**
     * @brief Calculates and returns the projection matrix for the camera.
     * @return The projection matrix as a matrix4.
     */
    matrix4 projectionMatrix();

    /**
     * @brief Serializes the camera component's data into the given record.
     * @param record Pointer to the DataRecord to serialize into.
     */
    void serializeComponent( DataRecord* record );

    /**
     * @brief Deserializes the camera component's data from the given record.
     * @param record Pointer to the DataRecord to deserialize from.
     */
    void deserializeComponent( DataRecord* record );

    /**
     * @brief Sets the camera's pitch (rotation around the X axis).
     * @param angle The pitch angle in degrees or radians.
     */
    void setPitch( const float angle );

    /**
     * @brief Sets the camera's yaw (rotation around the Y axis).
     * @param angle The yaw angle in degrees or radians.
     */
    void setYaw( const float angle );

    /**
     * @brief Sets the camera's roll (rotation around the Z axis).
     * @param angle The roll angle in degrees or radians.
     */
    void setRoll( const float angle );

    /**
     * @brief Adds to the camera's pitch (rotation around the X axis).
     * @param angle The amount to add to the pitch.
     */
    void addPitch( const float angle );

    /**
     * @brief Adds to the camera's yaw (rotation around the Y axis).
     * @param angle The amount to add to the yaw.
     */
    void addYaw( const float angle );

    /**
     * @brief Adds to the camera's roll (rotation around the Z axis).
     * @param angle The amount to add to the roll.
     */
    void addRoll( const float angle );

    /**
     * @brief Gets the camera's Euler rotation as a vector.
     * @return Reference to the vector3 representing Euler rotation.
     */
    const vector3& getEulerRotation() const;

    /**
     * @brief Gets the camera's sensitivity value.
     * @return The sensitivity as a float.
     */
    const float getSensitivity() const;

    /**
     * @brief Sets the camera's sensitivity value.
     * @param sensitivity The new sensitivity value.
     */
    void setSensitivity( const float sensitivity );

    // Transform transform; //!< The transform associated with this camera.

    float fov;    //!< Field of view angle for the camera.
    float fnear;  //!< Near clipping plane distance.
    float ffar;   //!< Far clipping plane distance.
    float aspect; //!< Aspect ratio of the camera.
    bool primary; //!< Whether this camera is the primary camera.

protected:
    vector3
        m_eulerRotation; //!< Euler rotation (pitch, yaw, roll) of the camera.

    float m_sensitivity = 1.f; //!< Sensitivity value for camera movement.

    bool m_rotationIsDirty; //!< Flag indicating if the rotation is dirty and
                            //!< needs updating.
};

} // namespace SquirrelEngine

#endif
