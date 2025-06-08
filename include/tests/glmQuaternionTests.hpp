/**
 *
 * @file glmQuaternionTests.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-07
 *
 */

#ifndef GLMQUATERNIONTESTS_HPP
#define GLMQUATERNIONTESTS_HPP
#pragma once

namespace SquirrelEngine {

namespace GLMQuatTests {

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
}; // namespace GLMQuatTests

} // namespace SquirrelEngine

#endif
