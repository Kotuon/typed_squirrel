/**
 *
 * @file objectRenderer.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the ObjectRenderer class, which handles rendering of entities
 * in SquirrelEngine.
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

/**
 * @brief Handles rendering of entities in SquirrelEngine.
 */
class ObjectRenderer : public System {
public:
    /**
     * @brief Default constructor for ObjectRenderer.
     */
    ObjectRenderer();

    /**
     * @brief Renders all entities.
     */
    void render();
};

} // namespace SquirrelEngine

#endif
