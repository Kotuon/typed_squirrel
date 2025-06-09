/**
 *
 * @file quaternion.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Quaternion class, which provides quaternion math for
 * SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#pragma once

namespace SquirrelEngine {

/**
 * @brief Represents a quaternion for 3D rotations and math.
 */
class Quaternion {
public:
    /**
     * @brief Default constructor for Quaternion.
     */
    Quaternion();

    /**
     * @brief Copy constructor for Quaternion.
     * @param other The quaternion to copy from.
     */
    Quaternion( const Quaternion& other );

    /**
     * @brief Constructs a Quaternion from components.
     * @param w_ Scalar part.
     * @param i_ X component.
     * @param j_ Y component.
     * @param k_ Z component.
     */
    Quaternion( const float w_, const float i_, const float j_,
                const float k_ );

    /**
     * @brief Destructor for Quaternion.
     */
    ~Quaternion();

    /**
     * @brief Assignment operator.
     * @param other The quaternion to assign from.
     * @return Reference to this quaternion.
     */
    Quaternion& operator=( const Quaternion& other );

    /**
     * @brief Addition assignment operator.
     * @param rhs The quaternion to add.
     * @return Reference to this quaternion.
     */
    Quaternion& operator+=( const Quaternion& rhs );

    /**
     * @brief Subtraction assignment operator.
     * @param rhs The quaternion to subtract.
     * @return Reference to this quaternion.
     */
    Quaternion& operator-=( const Quaternion& rhs );

    /**
     * @brief Multiplication assignment operator (quaternion).
     * @param rhs The quaternion to multiply by.
     * @return Reference to this quaternion.
     */
    Quaternion& operator*=( const Quaternion& rhs );

    /**
     * @brief Multiplication assignment operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Reference to this quaternion.
     */
    Quaternion& operator*=( const float scaler );

    /**
     * @brief Unary negation operator.
     * @return Negated quaternion.
     */
    const Quaternion operator-() const;

    /**
     * @brief Addition operator.
     * @param rhs The quaternion to add.
     * @return Resulting quaternion.
     */
    const Quaternion operator+( const Quaternion& rhs ) const;

    /**
     * @brief Subtraction operator.
     * @param rhs The quaternion to subtract.
     * @return Resulting quaternion.
     */
    const Quaternion operator-( const Quaternion& rhs ) const;

    /**
     * @brief Multiplication operator (quaternion).
     * @param rhs The quaternion to multiply by.
     * @return Resulting quaternion.
     */
    const Quaternion operator*( const Quaternion& rhs ) const;

    /**
     * @brief Multiplication operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Resulting quaternion.
     */
    const Quaternion operator*( const float scaler ) const;

    /**
     * @brief Computes the dot product with another quaternion.
     * @param other The other quaternion.
     * @return The dot product.
     */
    float dot( const Quaternion& other ) const;

    /**
     * @brief Computes the norm (magnitude) of the quaternion.
     * @return The norm.
     */
    float norm() const;

    /**
     * @brief Computes the squared norm of the quaternion.
     * @return The squared norm.
     */
    float normSquared() const;

    /**
     * @brief Normalizes the quaternion.
     * @return Reference to this quaternion.
     */
    Quaternion& normalize();

    /**
     * @brief Returns the conjugate of the quaternion.
     * @return The conjugated quaternion.
     */
    const Quaternion conjugate() const;

    /**
     * @brief Rotates a vector by this quaternion (in-place).
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    void rotateVector( float& x, float& y, float& z ) const;

    /**
     * @brief Rotates a vector by this quaternion (in-place).
     * @param vec Pointer to a 3-element vector.
     */
    void rotateVector( float* vec ) const;

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param roll Rotation around X axis (radians).
     * @param pitch Rotation around Y axis (radians).
     * @param yaw Rotation around Z axis (radians).
     * @return The resulting quaternion.
     */
    static const Quaternion fromEuler( const float roll, const float pitch,
                                       const float yaw );

    /**
     * @brief Creates a quaternion from an axis and angle.
     * @param x X component of the axis.
     * @param y Y component of the axis.
     * @param z Z component of the axis.
     * @param angle Angle in radians.
     * @return The resulting quaternion.
     */
    static const Quaternion fromAxisAngle( const float x, const float y,
                                           const float z, const float angle );

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
