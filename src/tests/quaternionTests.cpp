/**
 *
 * @file quaternionTests.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-07
 *
 */

#include "tests/quaternionTests.hpp"
#include "quaternion.hpp"
#include "utils/timer.hpp"

namespace SquirrelEngine {

namespace QuatTests {

Timer timer;

int testCount = 100000;

} // namespace QuatTests

void QuatTests::init() { timer.openFile( "RegQuatTest" ); }
void QuatTests::end() { timer.saveFile(); }

void QuatTests::construction() {
    timer.run( []() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            Quaternion q( 1.f, 2.f, 3.f, 4.f );
    } );
}

void QuatTests::copyConstruct() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            Quaternion q2( q1 );
    } );
}

void QuatTests::assignment() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 = Quaternion( q1 );
    } );
}
void QuatTests::addAssign() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 += q1;
    } );
}
void QuatTests::subAssign() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 -= q1;
    } );
}
void QuatTests::mulQuatAssign() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 *= q1;
    } );
}
void QuatTests::mulScaleAssign() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    timer.run( [&q, scale]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q *= scale;
    } );
}

void QuatTests::negation() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 = -q1;
    } );
}

void QuatTests::add() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );
    Quaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q3 = q2 + q1;
    } );
}
void QuatTests::sub() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );
    Quaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q3 = q2 - q1;
    } );
}
void QuatTests::mulQuat() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );
    Quaternion q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q3 = q2 * q1;
    } );
}
void QuatTests::mulScale() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    Quaternion q3;

    timer.run( [q1, scale, &q3]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q3 = q1 * scale;
    } );
}

void QuatTests::dot() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2( 1.f, 2.f, 3.f, 4.f );
    float dotResult;

    timer.run( [q1, q2, &dotResult]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            dotResult = q1.dot( q2 );
    } );
}

void QuatTests::norm() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );
    float normResult;

    timer.run( [q, &normResult]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            normResult = q.norm();
    } );
}
void QuatTests::normSquared() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );
    float normSquaredResult;

    timer.run( [q, &normSquaredResult]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            normSquaredResult = q.normSquared();
    } );
}

void QuatTests::normalize() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );

    timer.run( [&q]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q.normalize();
    } );
}
void QuatTests::conjugate() {
    Quaternion q1( 1.f, 2.f, 3.f, 4.f );
    Quaternion q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q2 = q1.conjugate();
    } );
}

void QuatTests::rotateVectorFromFloats() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [q, &x, &y, &z]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q.rotateVector( x, y, z );
    } );
}
void QuatTests::rotateVectorFromArray() {
    Quaternion q( 1.f, 2.f, 3.f, 4.f );
    float xyz[3] = { 1.f, 2.f, 3.f };

    timer.run( [q, &xyz]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q.rotateVector( xyz );
    } );
}

void QuatTests::fromEuler() {
    Quaternion q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [&q, x, y, z]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q = Quaternion::fromEuler( x, y, z );
    } );
}
void QuatTests::fromAxisAngle() {
    Quaternion q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;
    float angle = 4.f;

    timer.run( [&q, x, y, z, angle]() {
        for ( int i = 0; i < QuatTests::testCount; ++i )
            q = Quaternion::fromAxisAngle( x, y, z, angle );
    } );
}

} // namespace SquirrelEngine
