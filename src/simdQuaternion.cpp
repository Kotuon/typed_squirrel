/**
 *
 * @file simdQuaternion.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-08
 *
 */

#include <cmath>
#include <xmmintrin.h>

#include "simdQuaternion.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for SIMDQuaternion.
 */
SIMDQuaternion::SIMDQuaternion() : w( 1.f ), i( 0.f ), j( 0.f ), k( 0.f ) {}

/**
 * @brief Copy constructor for SIMDQuaternion.
 * @param other The SIMDQuaternion to copy from.
 */
SIMDQuaternion::SIMDQuaternion( const SIMDQuaternion& other )
    : w( other.w ), i( other.i ), j( other.j ), k( other.k ) {}

/**
 * @brief Constructs a SIMDQuaternion from components.
 * @param w_ Scalar part.
 * @param i_ X component.
 * @param j_ Y component.
 * @param k_ Z component.
 */
SIMDQuaternion::SIMDQuaternion( const float w_, const float i_, const float j_,
                                const float k_ )
    : w( w_ ), i( i_ ), j( j_ ), k( k_ ) {}

/**
 * @brief Destructor for SIMDQuaternion.
 */
SIMDQuaternion::~SIMDQuaternion() {}

/**
 * @brief Assignment operator.
 * @param other The SIMDQuaternion to assign from.
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::operator=( const SIMDQuaternion& other ) {
    w = other.w;
    i = other.i;
    j = other.j;
    k = other.k;

    return *this;
}

/**
 * @brief Addition assignment operator.
 * @param rhs The SIMDQuaternion to add.
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::operator+=( const SIMDQuaternion& rhs ) {
    w += rhs.w;
    i += rhs.i;
    j += rhs.j;
    k += rhs.k;

    return *this;
}

/**
 * @brief Subtraction assignment operator.
 * @param rhs The SIMDQuaternion to subtract.
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::operator-=( const SIMDQuaternion& rhs ) {
    w -= rhs.w;
    i -= rhs.i;
    j -= rhs.j;
    k -= rhs.k;

    return *this;
}

/**
 * @brief Multiplication assignment operator (SIMDQuaternion).
 * @param rhs The SIMDQuaternion to multiply by.
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::operator*=( const SIMDQuaternion& rhs ) {
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
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::operator*=( const float scaler ) {
    w *= scaler;
    i *= scaler;
    j *= scaler;
    k *= scaler;

    return *this;
}

/**
 * @brief Unary negation operator.
 * @return Negated SIMDQuaternion.
 */
const SIMDQuaternion SIMDQuaternion::operator-() const {
    return SIMDQuaternion( -w, -i, -j, -k );
}

/**
 * @brief Addition operator.
 * @param rhs The SIMDQuaternion to add.
 * @return Resulting SIMDQuaternion.
 */
const SIMDQuaternion
SIMDQuaternion::operator+( const SIMDQuaternion& rhs ) const {
    __m128 q0 = _mm_load_ps( a );
    __m128 q1 = _mm_load_ps( rhs.a );

    __m128 a0 = _mm_add_ps( q0, q1 );

    SIMDQuaternion result;
    _mm_store_ps( result.a, a0 );

    return result;
}

/**
 * @brief Subtraction operator.
 * @param rhs The SIMDQuaternion to subtract.
 * @return Resulting SIMDQuaternion.
 */
const SIMDQuaternion
SIMDQuaternion::operator-( const SIMDQuaternion& rhs ) const {
    __m128 q0 = _mm_load_ps( a );
    __m128 q1 = _mm_load_ps( rhs.a );

    __m128 a0 = _mm_sub_ps( q0, q1 );

    SIMDQuaternion result;
    _mm_store_ps( result.a, a0 );

    return result;
}

/**
 * @brief Multiplication operator (SIMDQuaternion).
 * @param rhs The SIMDQuaternion to multiply by.
 * @return Resulting SIMDQuaternion.
 */
const SIMDQuaternion
SIMDQuaternion::operator*( const SIMDQuaternion& rhs ) const {
    __m128 q0 = _mm_load_ps( a );
    __m128 q1 = _mm_load_ps( rhs.a );

    // Multiplying quaternions together
    __m128 m0 = _mm_mul_ps( q0, q1 );
    __m128 m1 =
        _mm_mul_ps( q0, _mm_shuffle_ps( q1, q1, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );
    __m128 m2 =
        _mm_mul_ps( q0, _mm_shuffle_ps( q1, q1, _MM_SHUFFLE( 1, 0, 3, 2 ) ) );
    __m128 m3 =
        _mm_mul_ps( q0, _mm_shuffle_ps( q1, q1, _MM_SHUFFLE( 0, 1, 2, 3 ) ) );

    // Result for w
    __m128 wMask = _mm_set_ps( -0.f, -0.f, -0.f, 0.f );
    __m128 im0 = _mm_xor_ps( wMask, m0 );

    __m128 rw0 = _mm_add_ps(
        im0, _mm_shuffle_ps( im0, im0, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );
    __m128 rw1 = _mm_add_ps(
        rw0, _mm_shuffle_ps( rw0, rw0, _MM_SHUFFLE( 1, 0, 3, 2 ) ) );

    // Result for i
    __m128 iMask = _mm_set_ps( -0.f, 0.f, 0.f, 0.f );
    __m128 im1 = _mm_xor_ps( iMask, m1 );
    __m128 ri0 = _mm_add_ps(
        im1, _mm_shuffle_ps( im1, im1, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );
    __m128 ri1 = _mm_add_ps(
        ri0, _mm_shuffle_ps( ri0, ri0, _MM_SHUFFLE( 1, 0, 3, 2 ) ) );

    // Result for j
    __m128 jMask = _mm_set_ps( 0.f, 0.f, -0.f, 0.f );
    __m128 im2 = _mm_xor_ps( jMask, m2 );
    __m128 rj0 = _mm_add_ps(
        im2, _mm_shuffle_ps( im2, im2, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );
    __m128 rj1 = _mm_add_ps(
        rj0, _mm_shuffle_ps( rj0, rj0, _MM_SHUFFLE( 1, 0, 3, 2 ) ) );

    // Result for k
    __m128 kMask = _mm_set_ps( 0.f, -0.f, 0.f, 0.f );
    __m128 im3 = _mm_xor_ps( kMask, m3 );
    __m128 rk0 = _mm_add_ps(
        im3, _mm_shuffle_ps( im3, im3, _MM_SHUFFLE( 2, 3, 0, 1 ) ) );
    __m128 rk1 = _mm_add_ps(
        rk0, _mm_shuffle_ps( rk0, rk0, _MM_SHUFFLE( 1, 0, 3, 2 ) ) );

    SIMDQuaternion result;
    _mm_store_ss( &( result.a[0] ), rw1 );
    _mm_store_ss( &( result.a[1] ), ri1 );
    _mm_store_ss( &( result.a[2] ), rj1 );
    _mm_store_ss( &( result.a[3] ), rk1 );

    return result;
}

/**
 * @brief Multiplication operator (scalar).
 * @param scaler The scalar to multiply by.
 * @return Resulting SIMDQuaternion.
 */
const SIMDQuaternion SIMDQuaternion::operator*( const float scaler ) const {
    __m128 q0 = _mm_load_ps( a );
    __m128 s0 = _mm_set_ps( scaler, scaler, scaler, scaler );

    __m128 a0 = _mm_mul_ps( q0, s0 );

    SIMDQuaternion result;
    _mm_store_ps( result.a, a0 );

    return result;
}

/**
 * @brief Computes the dot product with another SIMDQuaternion.
 * @param other The other SIMDQuaternion.
 * @return The dot product.
 */
float SIMDQuaternion::dot( const SIMDQuaternion& other ) const {
    return w * other.w + i * other.i + j * other.j + k * other.k;
}

/**
 * @brief Computes the norm (magnitude) of the SIMDQuaternion.
 * @return The norm.
 */
float SIMDQuaternion::norm() const {
    return sqrt( w * w + i * i + j * j + k * k );
}

/**
 * @brief Computes the squared norm of the SIMDQuaternion.
 * @return The squared norm.
 */
float SIMDQuaternion::normSquared() const {
    return w * w + i * i + j * j + k * k;
}

/**
 * @brief Normalizes the SIMDQuaternion.
 * @return Reference to this SIMDQuaternion.
 */
SIMDQuaternion& SIMDQuaternion::normalize() {
    const float recpLength = 1.f / norm();

    w *= recpLength;
    i *= recpLength;
    j *= recpLength;
    k *= recpLength;

    return *this;
}

/**
 * @brief Returns the conjugate of the SIMDQuaternion.
 * @return The conjugated SIMDQuaternion.
 */
const SIMDQuaternion SIMDQuaternion::conjugate() const {
    return SIMDQuaternion( w, -i, -j, -k );
}

/**
 * @brief Rotates a vector by this SIMDQuaternion (in-place).
 * @param x X component of the vector.
 * @param y Y component of the vector.
 * @param z Z component of the vector.
 */
void SIMDQuaternion::rotateVector( float& x, float& y, float& z ) const {
    // Algorithm from: https://raw.org/proof/vector-rotation-using-quaternions/
    const float ti = 2.f * ( j * z - k * y );
    const float tj = 2.f * ( k * x - i * z );
    const float tk = 2.f * ( i * y - j * x );

    x = x + w * ti + ( j * z - k * y );
    y = y + w * tj + ( k * x - i * z );
    z = z + w * tk + ( i * y - j * x );
}

/**
 * @brief Rotates a vector by this SIMDQuaternion (in-place).
 * @param vec Pointer to a 3-element vector.
 */
void SIMDQuaternion::rotateVector( float* vec ) const {
    // Algorithm from: https://raw.org/proof/vector-rotation-using-quaternions/
    const float ti = 2.f * ( j * vec[2] - k * vec[1] );
    const float tj = 2.f * ( k * vec[3] - i * vec[2] );
    const float tk = 2.f * ( i * vec[1] - j * vec[3] );

    vec[0] = vec[0] + w * ti + ( j * vec[2] - k * vec[1] );
    vec[1] = vec[1] + w * tj + ( k * vec[3] - i * vec[2] );
    vec[2] = vec[2] + w * tk + ( i * vec[1] - j * vec[3] );
}

/**
 * @brief Creates a SIMDQuaternion from Euler angles.
 * @param roll Rotation around X axis (radians).
 * @param pitch Rotation around Y axis (radians).
 * @param yaw Rotation around Z axis (radians).
 * @return The resulting SIMDQuaternion.
 */
const SIMDQuaternion SIMDQuaternion::fromEuler( const float roll,
                                                const float pitch,
                                                const float yaw ) {
    const float cr = cos( roll * 0.5f );
    const float sr = sin( roll * 0.5f );
    const float cp = cos( pitch * 0.5f );
    const float sp = sin( pitch * 0.5f );
    const float cy = cos( yaw * 0.5f );
    const float sy = sin( yaw * 0.5f );

    return SIMDQuaternion(
        cr * cp * cy + sr * sp * sy, sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy );
}

/**
 * @brief Creates a SIMDQuaternion from an axis and angle.
 * @param x X component of the axis.
 * @param y Y component of the axis.
 * @param z Z component of the axis.
 * @param angle Angle in radians.
 * @return The resulting SIMDQuaternion.
 */
const SIMDQuaternion SIMDQuaternion::fromAxisAngle( const float x,
                                                    const float y,
                                                    const float z,
                                                    const float angle ) {

    const float halfAngle = angle * 0.5f;

    const float sAngle = sinf( halfAngle );
    const float cAngle = cosf( halfAngle );

    float sNorm = sAngle / sqrtf( x * x + y * y + z * z );

    return SIMDQuaternion( cAngle, x * sNorm, y * sNorm, z * sNorm );
}

} // namespace SquirrelEngine
