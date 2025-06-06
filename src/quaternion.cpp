/**
 *
 * @file quaternion.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-06
 *
 */

#include "quaternion.hpp"

namespace SquirrelEngine {

Quaternion::Quaternion() : w( 1.f ), i( 0.f ), j( 0.f ), k( 0.f ) {}

Quaternion::Quaternion( const Quaternion& other )
    : w( other.w ), i( other.i ), j( other.j ), k( other.k ) {}

Quaternion::Quaternion( const Quaternion&& other )
    : w( other.w ), i( other.i ), j( other.j ), k( other.k ) {}

Quaternion::Quaternion( float w_, float i_, float j_, float k_ )
    : w( w_ ), i( i_ ), j( j_ ), k( k_ ) {}

Quaternion::~Quaternion() {}

Quaternion& Quaternion::operator=( const Quaternion& other ) {
    return *this = Quaternion( other );
}

Quaternion& Quaternion::operator=( const Quaternion&& other ) {
    w = other.w;
    i = other.i;
    j = other.j;
    k = other.k;

    return *this;
}

Quaternion& Quaternion::operator+=( const Quaternion& rhs ) {
    w += rhs.w;
    i += rhs.i;
    j += rhs.j;
    k += rhs.k;

    return *this;
}

Quaternion& Quaternion::operator-=( const Quaternion& rhs ) {
    w -= rhs.w;
    i -= rhs.i;
    j -= rhs.j;
    k -= rhs.k;

    return *this;
}

Quaternion& Quaternion::operator*=( const Quaternion& rhs ) {
    float w1 = w;
    float i1 = i;
    float j1 = j;
    float k1 = k;

    float w2 = rhs.w;
    float i2 = rhs.i;
    float j2 = rhs.j;
    float k2 = rhs.k;

    w = ( w1 * w2 ) - ( i1 * i2 ) - ( j1 * j2 ) - ( k1 * k2 );
    i = ( w1 * i2 ) + ( i1 * w2 ) + ( j1 * k2 ) - ( k1 * j2 );
    j = ( w1 * j2 ) - ( i1 * k2 ) + ( j1 * w2 ) + ( k1 * i2 );
    k = ( w1 * k2 ) + ( i1 * j2 ) - ( j1 * i2 ) + ( k1 * w2 );

    return *this;
}

Quaternion& Quaternion::operator*=( const float scaler ) {
    w *= scaler;
    i *= scaler;
    j *= scaler;
    k *= scaler;

    return *this;
}

const Quaternion Quaternion::operator-() const {
    return Quaternion( -w, -i, -j, -k );
}

const Quaternion Quaternion::operator+( const Quaternion& rhs ) const {
    return Quaternion( *this ) += rhs;
}

const Quaternion Quaternion::operator-( const Quaternion& rhs ) const {
    return Quaternion( *this ) -= rhs;
}

const Quaternion Quaternion::operator*( const Quaternion& rhs ) const {
    return Quaternion( *this ) *= rhs;
}

const Quaternion Quaternion::operator*( const float scaler ) const {
    return Quaternion( *this ) *= scaler;
}



}; // namespace SquirrelEngine
