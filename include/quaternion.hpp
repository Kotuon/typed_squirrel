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

#include "math_types.hpp"
#include <numbers>

namespace SquirrelEngine {

/**
 * @brief Represents a quaternion for 3D rotations and math.
 */
class Quaternion {
public:
    /**
     * @brief Default constructor for Quaternion.
     */
    constexpr Quaternion() : w( 1.f ), i( 0.f ), j( 0.f ), k( 0.f ) {}

    constexpr Quaternion( const float value )
        : w( value ), i( value ), j( value ), k( value ) {}

    /**
     * @brief Copy constructor for Quaternion.
     * @param other The quaternion to copy from.
     */
    constexpr Quaternion( const Quaternion& other )
        : w( other.w ), i( other.i ), j( other.j ), k( other.k ) {}

    /**
     * @brief Constructs a Quaternion from components.
     * @param w_ Scalar part.
     * @param i_ X component.
     * @param j_ Y component.
     * @param k_ Z component.
     */
    constexpr Quaternion( const float w_, const float i_, const float j_,
                          const float k_ )
        : w( w_ ), i( i_ ), j( j_ ), k( k_ ) {}

    /**
     * @brief Destructor for Quaternion.
     */
    constexpr ~Quaternion() {}

    /**
     * @brief Assignment operator.
     * @param other The quaternion to assign from.
     * @return Reference to this quaternion.
     */
    constexpr Quaternion& operator=( const Quaternion& other ) {
        w = other.w;
        i = other.i;
        j = other.j;
        k = other.k;

        return *this;
    }

    /**
     * @brief Addition assignment operator.
     * @param rhs The quaternion to add.
     * @return Reference to this quaternion.
     */
    constexpr Quaternion& operator+=( const Quaternion& rhs ) {
        w += rhs.w;
        i += rhs.i;
        j += rhs.j;
        k += rhs.k;

        return *this;
    }

    /**
     * @brief Subtraction assignment operator.
     * @param rhs The quaternion to subtract.
     * @return Reference to this quaternion.
     */
    constexpr Quaternion& operator-=( const Quaternion& rhs ) {
        w -= rhs.w;
        i -= rhs.i;
        j -= rhs.j;
        k -= rhs.k;

        return *this;
    }

    /**
     * @brief Multiplication assignment operator (quaternion).
     * @param rhs The quaternion to multiply by.
     * @return Reference to this quaternion.
     */
    constexpr Quaternion& operator*=( const Quaternion& rhs ) {
        const float w1 = w;
        const float i1 = i;
        const float j1 = j;
        const float k1 = k;

        const float w2 = rhs.w;
        const float i2 = rhs.i;
        const float j2 = rhs.j;
        const float k2 = rhs.k;

        w = ( w1 * w2 ) - ( i1 * i2 ) - ( j1 * j2 ) - ( k1 * k2 );
        i = ( w1 * i2 ) + ( i1 * w2 ) + ( j1 * k2 ) - ( k1 * j2 );
        j = ( w1 * j2 ) - ( i1 * k2 ) + ( j1 * w2 ) + ( k1 * i2 );
        k = ( w1 * k2 ) + ( i1 * j2 ) - ( j1 * i2 ) + ( k1 * w2 );

        return *this;
    }

    /**
     * @brief Multiplication assignment operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Reference to this quaternion.
     */
    constexpr Quaternion& operator*=( const float scaler ) {
        w *= scaler;
        i *= scaler;
        j *= scaler;
        k *= scaler;

        return *this;
    }

    /**
     * @brief Unary negation operator.
     * @return Negated quaternion.
     */
    constexpr const Quaternion operator-() const {
        return Quaternion( -w, -i, -j, -k );
    }

    /**
     * @brief Addition operator.
     * @param rhs The quaternion to add.
     * @return Resulting quaternion.
     */
    constexpr const Quaternion operator+( const Quaternion& rhs ) const {
        return Quaternion( w + rhs.w, i + rhs.i, j + rhs.j, k + rhs.k );
    }

    /**
     * @brief Subtraction operator.
     * @param rhs The quaternion to subtract.
     * @return Resulting quaternion.
     */
    constexpr const Quaternion operator-( const Quaternion& rhs ) const {
        return Quaternion( w - rhs.w, i - rhs.i, j - rhs.j, k - rhs.k );
    }

    /**
     * @brief Multiplication operator (quaternion).
     * @param rhs The quaternion to multiply by.
     * @return Resulting quaternion.
     */
    constexpr const Quaternion operator*( const Quaternion& rhs ) const {
        return Quaternion(
            ( w * rhs.w ) - ( i * rhs.i ) - ( j * rhs.j ) - ( k * rhs.k ),
            ( w * rhs.i ) + ( i * rhs.w ) + ( j * rhs.k ) - ( k * rhs.j ),
            ( w * rhs.j ) - ( i * rhs.k ) + ( j * rhs.w ) + ( k * rhs.i ),
            ( w * rhs.k ) + ( i * rhs.j ) - ( j * rhs.i ) + ( k * rhs.w ) );
    }

    /**
     * @brief Multiplication operator (scalar).
     * @param scaler The scalar to multiply by.
     * @return Resulting quaternion.
     */
    constexpr const Quaternion operator*( const float scaler ) const {
        return Quaternion( w * scaler, i * scaler, j * scaler, k * scaler );
    }

    constexpr const vector3 operator*( const vector3 vec ) const {
        const vector3 t = 2.f * glm::cross( vector3( i, j, k ), vec );
        return vec + t * w + glm::cross( vector3( i, j, k ), t );
    }

    /**
     * @brief Computes the dot product with another quaternion.
     * @param other The other quaternion.
     * @return The dot product.
     */
    constexpr float dot( const Quaternion& other ) const {
        return w * other.w + i * other.i + j * other.j + k * other.k;
    }

    /**
     * @brief Computes the norm (magnitude) of the quaternion.
     * @return The norm.
     */
    float norm() const { return sqrtf( w * w + i * i + j * j + k * k ); }

    /**
     * @brief Computes the squared norm of the quaternion.
     * @return The squared norm.
     */
    constexpr float normSquared() const {
        return w * w + i * i + j * j + k * k;
    }

    /**
     * @brief Normalizes the quaternion.
     * @return Reference to this quaternion.
     */
    Quaternion& normalize() {
        const float recpLength = 1.f / norm();

        w *= recpLength;
        i *= recpLength;
        j *= recpLength;
        k *= recpLength;

        return *this;
    }

    /**
     * @brief Returns the conjugate of the quaternion.
     * @return The conjugated quaternion.
     */
    constexpr const Quaternion conjugate() const {
        return Quaternion( w, -i, -j, -k );
    }

    /**
     * @brief Rotates a vector by this quaternion (in-place).
     * @param x X component of the vector.
     * @param y Y component of the vector.
     * @param z Z component of the vector.
     */
    constexpr void rotateVector( float& x, float& y, float& z ) const {
        // Algorithm from:
        // https://raw.org/proof/vector-rotation-using-quaternions/
        const float ti = 2.f * ( j * z - k * y );
        const float tj = 2.f * ( k * x - i * z );
        const float tk = 2.f * ( i * y - j * x );

        x = x + w * ti + ( j * z - k * y );
        y = y + w * tj + ( k * x - i * z );
        z = z + w * tk + ( i * y - j * x );
    }

    /**
     * @brief Rotates a vector by this quaternion (in-place).
     * @param vec Pointer to a 3-element vector.
     */
    constexpr void rotateVector( float* vec ) const {
        // Algorithm from:
        // https://raw.org/proof/vector-rotation-using-quaternions/
        const float ti = 2.f * ( j * vec[2] - k * vec[1] );
        const float tj = 2.f * ( k * vec[3] - i * vec[2] );
        const float tk = 2.f * ( i * vec[1] - j * vec[3] );

        vec[0] = vec[0] + w * ti + ( j * vec[2] - k * vec[1] );
        vec[1] = vec[1] + w * tj + ( k * vec[3] - i * vec[2] );
        vec[2] = vec[2] + w * tk + ( i * vec[1] - j * vec[3] );
    }

    const vector3 getEulerRotation() const {
        vector3 eulerRotation;

        // Pitch
        const float sp = 2.f * ( w * i + j * k );
        const float cp = 1.f - sp;

        eulerRotation.x = std::atan2f( sp, cp );

        // Yaw
        const float sy = std::sqrt( 1.f + 2.f * ( w * j - i * k ) );
        const float cy = std::sqrt( 1.f - 2.f * ( w * j - i * k ) );

        eulerRotation.y = 2.f * std::atan2f( sy, cy ) -
                          static_cast< float >( std::numbers::pi ) / 2.f;

        // Roll
        const float sr = 2.f * ( w * i + k * j );
        const float cr = 1.f - sr;

        eulerRotation.z = std::atan2f( sr, cr );

        return eulerRotation;
    }

    /**
     * @brief Creates a quaternion from Euler angles.
     * @param roll Rotation around Z axis (radians).
     * @param pitch Rotation around X axis (radians).
     * @param yaw Rotation around Y axis (radians).
     * @return The resulting quaternion.
     */
    static const Quaternion fromEuler( const float roll, const float pitch,
                                       const float yaw ) {
        const float cr = cosf( roll * 0.5f );
        const float sr = sinf( roll * 0.5f );
        const float cp = cosf( pitch * 0.5f );
        const float sp = sinf( pitch * 0.5f );
        const float cy = cosf( yaw * 0.5f );
        const float sy = sinf( yaw * 0.5f );

        return Quaternion(
            cr * cp * cy + sr * sp * sy, sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy );
    }

    /**
     * @brief Creates a quaternion from an axis and angle.
     * @param x X component of the axis.
     * @param y Y component of the axis.
     * @param z Z component of the axis.
     * @param angle Angle in radians.
     * @return The resulting quaternion.
     */
    static const Quaternion fromAxisAngle( const float x, const float y,
                                           const float z, const float angle ) {
        const float halfAngle = angle * 0.5f;

        const float sAngle = sinf( halfAngle );
        const float cAngle = cosf( halfAngle );

        float sNorm = sAngle / sqrtf( x * x + y * y + z * z );

        return Quaternion( cAngle, x * sNorm, y * sNorm, z * sNorm );
    }

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
