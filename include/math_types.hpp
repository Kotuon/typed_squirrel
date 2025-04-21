
#ifndef MATH_TYPES_HPP
#define MATH_TYPES_HPP
#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

using vector2 = glm::vec2;
using vector3 = glm::vec3;
using vector4 = glm::vec4;
using quat = glm::quat;
using matrix3 = glm::mat3;
using matrix4 = glm::mat4;

#endif
