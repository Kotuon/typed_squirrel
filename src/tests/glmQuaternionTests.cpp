/**
 *
 * @file glmQuaternionTests.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-07
 *
 */

#include "tests/glmQuaternionTests.hpp"
#include "math_types.hpp"
#include "utils/timer.hpp"

namespace SquirrelEngine {

namespace GLMQuatTests {

Timer timer;

int testCount = 100000;

} // namespace GLMQuatTests

void GLMQuatTests::init() { timer.openFile( "GLMQuatTest" ); }
void GLMQuatTests::end() { timer.saveFile(); }

void GLMQuatTests::construction() {
    timer.run( []() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            quat q( 1.f, 2.f, 3.f, 4.f );
    } );
}

void GLMQuatTests::copyConstruct() {
    quat q1( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            quat q2( q1 );
    } );
}

void GLMQuatTests::assignment() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 = quat( q1 );
    } );
}
void GLMQuatTests::addAssign() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 += q1;
    } );
}
void GLMQuatTests::subAssign() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 -= q1;
    } );
}
void GLMQuatTests::mulQuatAssign() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 *= q1;
    } );
}
void GLMQuatTests::mulScaleAssign() {
    quat q( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    timer.run( [&q, scale]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q *= scale;
    } );
}

void GLMQuatTests::negation() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 = -q1;
    } );
}

void GLMQuatTests::add() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );
    quat q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q3 = q2 + q1;
    } );
}
void GLMQuatTests::sub() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );
    quat q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q3 = q2 - q1;
    } );
}
void GLMQuatTests::mulQuat() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );
    quat q3;

    timer.run( [q1, q2, &q3]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q3 = q2 * q1;
    } );
}
void GLMQuatTests::mulScale() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    float scale = 2.f;

    quat q3;

    timer.run( [q1, scale, &q3]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q3 = q1 * scale;
    } );
}

void GLMQuatTests::dot() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2( 1.f, 2.f, 3.f, 4.f );
    float dotResult;

    timer.run( [q1, q2, &dotResult]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            dotResult = glm::dot( q1, q2 );
    } );
}

void GLMQuatTests::norm() {
    quat q( 1.f, 2.f, 3.f, 4.f );
    float normResult;

    timer.run( [q, &normResult]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            normResult = glm::length( q );
    } );
}
void GLMQuatTests::normSquared() {
    quat q( 1.f, 2.f, 3.f, 4.f );
    float normSquaredResult;

    timer.run( [q, &normSquaredResult]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            normSquaredResult = glm::length2( q );
    } );
}

void GLMQuatTests::normalize() {
    quat q( 1.f, 2.f, 3.f, 4.f );

    timer.run( [&q]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            glm::normalize( q );
    } );
}
void GLMQuatTests::conjugate() {
    quat q1( 1.f, 2.f, 3.f, 4.f );
    quat q2;

    timer.run( [q1, &q2]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q2 = glm::conjugate( q1 );
    } );
}

void GLMQuatTests::rotateVectorFromFloats() {
    quat q( 1.f, 2.f, 3.f, 4.f );
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [q, &x, &y, &z]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            glm::rotate( q, { x, y, z } );
    } );
}
void GLMQuatTests::rotateVectorFromArray() {
    quat q( 1.f, 2.f, 3.f, 4.f );
    float xyz[3] = { 1.f, 2.f, 3.f };

    timer.run( [q, &xyz]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            glm::rotate( q, vector3( xyz[0], xyz[1], xyz[2] ) );
    } );
}

void GLMQuatTests::fromEuler() {
    quat q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;

    timer.run( [&q, x, y, z]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q = glm::quat( vector3( x, y, z ) );
    } );
}
void GLMQuatTests::fromAxisAngle() {
    quat q;
    float x = 1.f;
    float y = 2.f;
    float z = 3.f;
    float angle = 4.f;

    timer.run( [&q, x, y, z, angle]() {
        for ( int i = 0; i < GLMQuatTests::testCount; ++i )
            q = glm::angleAxis( angle, vector3( x, y, z ) );
    } );
}

} // namespace SquirrelEngine
