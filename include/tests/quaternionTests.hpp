/**
 *
 * @file quaternionTests.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-07
 *
 */

#ifndef QUATERNIONTESTS_HPP
#define QUATERNIONTESTS_HPP
#pragma once

namespace SquirrelEngine {

namespace QuatTests {

void init();
void end();

void construction();
void copyConstruct();

void assignment();
void addAssign();
void subAssign();
void mulQuatAssign();
void mulScaleAssign();

void negation();

void add();
void sub();
void mulQuat();
void mulScale();

void dot();

void norm();
void normSquared();

void normalize();
void conjugate();

void rotateVectorFromFloats();
void rotateVectorFromArray();

void fromEuler();
void fromAxisAngle();
}; // namespace QuatTests

} // namespace SquirrelEngine

#endif
