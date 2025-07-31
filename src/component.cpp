/**
 *
 * @file component.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Component base class for attaching behavior to entities
 * in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "component.hpp"
#include "entity.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor (protected to prevent direct instantiation).
 */
Component::Component() {}

/**
 * @brief Constructs a Component with the given parent entity.
 * @param t_parent Pointer to the parent Entity.
 */
Component::Component( Entity* t_parent ) : owner( t_parent ) {}

} // namespace SquirrelEngine
