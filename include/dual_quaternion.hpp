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

public:
    Quaternion real;
    Quaternion dual;
};

} // namespace SquirrelEngine
