/**
 *
 * @file component.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Component base class for attaching behavior to entities
 * in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {
class Entity;

class Component : public Object {
    /**
     * @brief Default constructor (protected to prevent direct instantiation).
     */
    Component();

public:
    /**
     * @brief Constructs a Component with the given parent entity.
     * @param t_parent Pointer to the parent Entity.
     */
    Component( Entity* t_parent );

    /**
     * @brief Virtual destructor for safe polymorphic deletion.
     */
    virtual ~Component() = default;

    Entity* parent; //!< Pointer to the parent entity of this component.
};

} // namespace SquirrelEngine

#endif
