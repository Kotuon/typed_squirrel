/**
 *
 * @file simdQuaternion.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-08
 *
 */

#ifndef SIMDQUATERNION_HPP
#define SIMDQUATERNION_HPP
#pragma once

namespace SquirrelEngine {

class SIMDQuaternion {
public:
    /**
     * @brief Default constructor for SIMDQuaternion.
     */
    SIMDQuaternion();

    /**
     * @brief Copy constructor for SIMDQuaternion.
     * @param other The SIMDQuaternion to copy from.
     */
    SIMDQuaternion( const SIMDQuaternion& other );

    /**
     * @brief Constructs a SIMDQuaternion from components.
     * @param w_ Scalar part.
     * @param i_ X component.
     * @param j_ Y component.
     * @param k_ Z component.
     */
    SIMDQuaternion( const float w_, const float i_, const float j_,
                    const float k_ );

    /**
     * @brief Destructor for SIMDQuaternion.
     */
    ~SIMDQuaternion();

    /**
     * @brief Assignment operator.
     * @param other The SIMDQuaternion to assign from.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& operator=( const SIMDQuaternion& other );

    /**
     * @brief Addition assignment operator.
     * @param rhs The SIMDQuaternion to add.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& operator+=( const SIMDQuaternion& rhs );

    /**
     * @brief Subtraction assignment operator.
     * @param rhs The SIMDQuaternion to subtract.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& operator-=( const SIMDQuaternion& rhs );

    /**
     * @brief Multiplication assignment operator (SIMDQuaternion).
     * @param rhs The SIMDQuaternion to multiply by.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& operator*=( const SIMDQuaternion& rhs );

    /**
     * @brief Multiplication assignment operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& operator*=( const float scaler );

    /**
     * @brief Unary negation operator.
     * @return Negated SIMDQuaternion.
     */
    const SIMDQuaternion operator-() const;

    /**
     * @brief Addition operator.
     * @param rhs The SIMDQuaternion to add.
     * @return Resulting SIMDQuaternion.
     */
    const SIMDQuaternion operator+( const SIMDQuaternion& rhs ) const;

    /**
     * @brief Subtraction operator.
     * @param rhs The SIMDQuaternion to subtract.
     * @return Resulting SIMDQuaternion.
     */
    const SIMDQuaternion operator-( const SIMDQuaternion& rhs ) const;

    /**
     * @brief Multiplication operator (SIMDQuaternion).
     * @param rhs The SIMDQuaternion to multiply by.
     * @return Resulting SIMDQuaternion.
     */
    const SIMDQuaternion operator*( const SIMDQuaternion& rhs ) const;

    /**
     * @brief Multiplication operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Resulting SIMDQuaternion.
     */
    const SIMDQuaternion operator*( const float scaler ) const;

    /**
     * @brief Computes the dot product with another SIMDQuaternion.
     * @param other The other SIMDQuaternion.
     * @return The dot product.
     */
    float dot( const SIMDQuaternion& other ) const;

    /**
     * @brief Computes the norm (magnitude) of the SIMDQuaternion.
     * @return The norm.
     */
    float norm() const;

    /**
     * @brief Computes the squared norm of the SIMDQuaternion.
     * @return The squared norm.
     */
    float normSquared() const;

    /**
     * @brief Normalizes the SIMDQuaternion.
     * @return Reference to this SIMDQuaternion.
     */
    SIMDQuaternion& normalize();

    /**
     * @brief Returns the conjugate of the SIMDQuaternion.
     * @return The conjugated SIMDQuaternion.
     */
    const SIMDQuaternion conjugate() const;

    /**
     * @brief Rotates a vector by this SIMDQuaternion (in-place).
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    void rotateVector( float& x, float& y, float& z ) const;

    /**
     * @brief Rotates a vector by this SIMDQuaternion (in-place).
     * @param vec Pointer to a 3-element vector.
     */
    void rotateVector( float* vec ) const;

    /**
     * @brief Creates a SIMDQuaternion from Euler angles.
     * @param roll Rotation around X axis (radians).
     * @param pitch Rotation around Y axis (radians).
     * @param yaw Rotation around Z axis (radians).
     * @return The resulting SIMDQuaternion.
     */
    static const SIMDQuaternion fromEuler( const float roll, const float pitch,
                                           const float yaw );

    /**
     * @brief Creates a SIMDQuaternion from an axis and angle.
     * @param x X component of the axis.
     * @param y Y component of the axis.
     * @param z Z component of the axis.
     * @param angle Angle in radians.
     * @return The resulting SIMDQuaternion.
     */
    static const SIMDQuaternion fromAxisAngle( const float x, const float y,
                                               const float z,
                                               const float angle );

public:
#if defined( _MSC_VER )
#pragma warning( push, 3 )
#pragma warning( disable : 4201 )
#endif
    union {
        float a[4] = { 0 };
        struct {
            float w; //!< Scalar part
            float i; //!< X component
            float j; //!< Y component
            float k; //!< Z component}
        };
    };
#if defined( _MSC_VER )
#pragma warning( default : 4201 )
#pragma warning( pop )
#endif
};

} // namespace SquirrelEngine

#endif
