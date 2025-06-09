/**
 *
 * @file simdQuaternionTests.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-08
 *
 */

#include "simdQuaternionTests.hpp"
#include "simdQuaternion.hpp"
#include "utils/timer.hpp"

namespace SquirrelEngine {

namespace SIMDQuatTests {

Timer timer;

int testCount = 100000;

} // namespace SIMDQuatTests

void SIMDQuatTests::init() { timer.openFile( "SIMDQuatTest" ); }
void SIMDQuatTests::end() { timer.saveFile(); }

void SIMDQuatTests::construction() {
    timer.run( []() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    } );
}

void SIMDQuatTests::copyConstruct() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            SIMDQuaternion q2( q1 );
    } );
}

void SIMDQuatTests::assignment() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 = SIMDQuaternion( q1 );
    } );
}
void SIMDQuatTests::addAssign() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 += q1;
    } );
}
void SIMDQuatTests::subAssign() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 -= q1;
    } );
}
void SIMDQuatTests::mulQuatAssign() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 *= q1;
    } );
}
void SIMDQuatTests::mulScaleAssign() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    timer.run( [&q, scale]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q *= scale;
    } );
}

void SIMDQuatTests::negation() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 = -q1;
    } );
}

void SIMDQuatTests::add() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q3 = q2 + q1;
    } );
}
void SIMDQuatTests::sub() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q3 = q2 - q1;
    } );
}
void SIMDQuatTests::mulQuat() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q3 = q2 * q1;
    } );
}
void SIMDQuatTests::mulScale() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    SIMDQuaternion q3;

    timer.run( [q1, scale, &q3]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q3 = q1 * scale;
    } );
}

void SIMDQuatTests::dot() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2( 1.f, 2.f, 3.f, 4.f );
    float dotResult;

    timer.run( [q1, q2, &dotResult]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            dotResult = q1.dot( q2 );
    } );
}

void SIMDQuatTests::norm() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    float normResult;

    timer.run( [q, &normResult]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            normResult = q.norm();
    } );
}
void SIMDQuatTests::normSquared() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    float normSquaredResult;

    timer.run( [q, &normSquaredResult]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            normSquaredResult = q.normSquared();
    } );
}

void SIMDQuatTests::normalize() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );

    timer.run( [&q]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q.normalize();
    } );
}
void SIMDQuatTests::conjugate() {
    SIMDQuaternion q1( 1.f, 2.f, 3.f, 4.f );
    SIMDQuaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q2 = q1.conjugate();
    } );
}

void SIMDQuatTests::rotateVectorFromFloats() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [q, &x, &y, &z]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q.rotateVector( x, y, z );
    } );
}
void SIMDQuatTests::rotateVectorFromArray() {
    SIMDQuaternion q( 1.f, 2.f, 3.f, 4.f );
    float xyz[3] = { 1.f, 2.f, 3.f };

    timer.run( [q, &xyz]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q.rotateVector( xyz );
    } );
}

void SIMDQuatTests::fromEuler() {
    SIMDQuaternion q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [&q, x, y, z]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q = SIMDQuaternion::fromEuler( x, y, z );
    } );
}
void SIMDQuatTests::fromAxisAngle() {
    SIMDQuaternion q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;
    float angle = 4.f;

    timer.run( [&q, x, y, z, angle]() {
        for ( int i = 0; i < SIMDQuatTests::testCount; ++i )
            q = SIMDQuaternion::fromAxisAngle( x, y, z, angle );
    } );
}

} // namespace SquirrelEngine
