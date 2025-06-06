/**
 *
 * @file objectRenderer.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-05-05
 *
 */

#ifndef OBJECTRENDERER_HPP
#define OBJECTRENDERER_HPP
#pragma once

#include <vector>

#include "system.hpp"

namespace SquirrelEngine {
class Entity;

class ObjectRenderer : public System {
public:
    ObjectRenderer();

    void render();
};

} // namespace SquirrelEngine

#endif
