/**
 *
 * @file dual_quaternion.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-10
 *
 */

#include "quaternion.hpp"

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

    // constexpr float norm() const { return real.norm(); }

    // constexpr float normSquared() const { return real.normSquared(); }

    constexpr DualQuaternion& normalize() {
        const float mag = real.dot( real );

        real *= 1.f / mag;
        dual *= 1.f / mag;

        return *this;
    }

    constexpr const DualQuaternion conjugate() const {
        return DualQuaternion( real.conjugate(), dual.conjugate() );
    }

public:
    Quaternion real;
    Quaternion dual;
};

} // namespace SquirrelEngine
