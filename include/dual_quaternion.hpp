/**
 *
 * @file dual_quaternion.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-10
 *
 */

#include "quaternion.hpp"

#include <numbers>

namespace SquirrelEngine {

class DualQuaternion {
public:
    constexpr DualQuaternion() : real(), dual() {}

    constexpr DualQuaternion( const DualQuaternion& other )
        : real( other.real ), dual( other.dual ) {}

    constexpr DualQuaternion( const Quaternion real_, const Quaternion dual_ )
        : real( real_ ), dual( dual_ ) {}

    constexpr DualQuaternion& operator=( const DualQuaternion& other ) {
        real = other.real;
        dual = other.dual;

        return *this;
    }

    constexpr DualQuaternion& operator+=( const DualQuaternion& rhs ) {
        real += rhs.real;
        dual += rhs.dual;

        return *this;
    }

    constexpr DualQuaternion& operator-=( const DualQuaternion& rhs ) {
        real -= rhs.real;
        dual -= rhs.dual;

        return *this;
    }

    constexpr DualQuaternion& operator*=( const DualQuaternion& rhs ) {
        real *= rhs.real;
        dual *= rhs.dual;

        return *this;
    }

    constexpr DualQuaternion& operator*=( const float scaler ) {
        real *= scaler;
        dual *= scaler;

        return *this;
    }

    constexpr const DualQuaternion operator-() const {
        return DualQuaternion( -real, -dual );
    }

    constexpr const DualQuaternion
    operator+( const DualQuaternion& rhs ) const {
        return DualQuaternion( real + rhs.real, dual + rhs.dual );
    }

    constexpr const DualQuaternion operator-( const DualQuaternion& rhs ) {
        return DualQuaternion( real - rhs.real, dual - rhs.dual );
    }

    constexpr const DualQuaternion operator*( const DualQuaternion& rhs ) {
        return DualQuaternion( real * rhs.real,
                               real * rhs.dual + dual * rhs.real );
    }

    constexpr const DualQuaternion operator*( const float scaler ) {
        return DualQuaternion( real * scaler, dual * scaler );
    }

    constexpr float dot( const DualQuaternion& other ) const {
        return real.dot( other.real );
    }

    float norm() const { return real.norm(); }

    constexpr float normSquared() const { return real.normSquared(); }

    constexpr DualQuaternion& normalize() {
        const float mag = real.dot( real );

        real *= 1.f / mag;
        dual *= 1.f / mag;

        return *this;
    }

    constexpr const DualQuaternion conjugateQuaternion() const {
        return DualQuaternion( real.conjugate(), dual.conjugate() );
    }

    constexpr const DualQuaternion conjugateDual() const {
        return DualQuaternion( real, -dual );
    }

    constexpr const DualQuaternion conjugateCombined() const {
        return DualQuaternion( real.conjugate(), -dual.conjugate() );
    }

    constexpr void setRotation( const Quaternion& t_rotation ) {
        dual *= real.conjugate();
        real = t_rotation;
        dual *= real;
    }

    constexpr void addRotation( const Quaternion& t_rotation ) {
        real = t_rotation * real;
    }

    constexpr const Quaternion& getRotation() const { return real; }

    const vector3 getEulerRotation() const {
        vector3 eulerRotation;

        // Roll
        const float sr = 2.f * ( real.w * real.i + real.j * real.k );
        const float cr = 1.f - sr;

        eulerRotation.x = std::atan2f( sr, cr );

        // Pitch
        const float sp =
            std::sqrt( 1.f + 2.f * ( real.w * real.j - real.i * real.k ) );
        const float cp = 1.f - sp;

        eulerRotation.y = 2.f * std::atan2f( sp, cp ) -
                          static_cast< float >( std::numbers::pi ) / 2.f;

        // Yaw
        const float sy = 2.f * ( real.w * real.i + real.k * real.j );
        const float cy = 1.f - sy;

        eulerRotation.z = std::atan2f( sy, cy );

        return eulerRotation;
    }

    constexpr void setTranslation( const vector3 trans ) {
        dual = ( Quaternion( 0.f, trans.x, trans.y, trans.z ) * 0.5f ) * real;
    }

    constexpr void addTranslation( const vector3 trans ) {
        dual += ( Quaternion( 0.f, trans.x, trans.y, trans.z ) * 0.5f ) * real;
    }

    constexpr const vector3 getTranslation() const {
        const Quaternion t = ( dual * 2.f ) * real.conjugate();
        return vector3( t.i, t.j, t.k );
    }

    constexpr const matrix4 getRotationMatrix() {
        normalize();

        const float& w = real.w;
        const float& i = real.i;
        const float& j = real.j;
        const float& k = real.k;

        const float w2 = real.w * real.w;
        const float i2 = real.i * real.i;
        const float j2 = real.j * real.j;
        const float k2 = real.k * real.k;

        matrix4 result = { w2 + i2 - j2 - k2,
                           2.f * i * j - 2.f * w * k,
                           2.f * i * k + 2.f * w * j,
                           1.f,
                           2.f * i * j + 2.f * w * k,
                           w2 - i2 + j2 - k2,
                           2.f * j * k - 2.f * w * i,
                           1.f,
                           2.f * i * k - 2.f * w * j,
                           2.f * j * k + 2.f * w * i,
                           w2 - i2 - j2 + k2,
                           1.f,
                           0.f,
                           0.f,
                           0.f,
                           1.f };

        return result;
    }

    constexpr const matrix4 getMatrix() {
        normalize();

        const float& w = real.w;
        const float& i = real.i;
        const float& j = real.j;
        const float& k = real.k;

        const float w2 = real.w * real.w;
        const float i2 = real.i * real.i;
        const float j2 = real.j * real.j;
        const float k2 = real.k * real.k;

        const vector3 t = getTranslation();

        matrix4 result = { w2 + i2 - j2 - k2,
                           2.f * i * j - 2.f * w * k,
                           2.f * i * k + 2.f * w * j,
                           t.x,
                           2.f * i * j + 2.f * w * k,
                           w2 - i2 + j2 - k2,
                           2.f * j * k - 2.f * w * i,
                           t.y,
                           2.f * i * k - 2.f * w * j,
                           2.f * j * k + 2.f * w * i,
                           w2 - i2 - j2 + k2,
                           t.z,
                           0.f,
                           0.f,
                           0.f,
                           1.f };

        return result;
    }

public:
    Quaternion real;
    Quaternion dual;
};

} // namespace SquirrelEngine
