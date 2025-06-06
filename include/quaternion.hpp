/**
 *
 * @file quaternion.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-06
 *
 */

#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#pragma once

#include "math_types.hpp"

namespace SquirrelEngine {

class Quaternion {
public:
    Quaternion();
    Quaternion( const Quaternion& other );
    Quaternion( const Quaternion&& other ) noexcept;
    Quaternion( float w_, float i_, float j_, float k_ );

    ~Quaternion();

    Quaternion& operator=( const Quaternion& other );
    Quaternion& operator=( const Quaternion&& other ) noexcept;

    Quaternion& operator+=( const Quaternion& rhs );
    Quaternion& operator-=( const Quaternion& rhs );
    Quaternion& operator*=( const Quaternion& rhs );
    Quaternion& operator*=( const float scaler );

    const Quaternion operator-() const;

    const Quaternion operator+( const Quaternion& rhs ) const;
    const Quaternion operator-( const Quaternion& rhs ) const;
    const Quaternion operator*( const Quaternion& rhs ) const;
    const Quaternion operator*( const float scaler ) const;

    float dot(const Quaternion& other) const;
    float norm() const;
    float normSqr() const;

public:
    float w;
    float i;
    float j;
    float k;
};

} // namespace SquirrelEngine

#endif
