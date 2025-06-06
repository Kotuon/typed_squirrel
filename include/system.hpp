/**
 *
 * @file system.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the System base class, which provides a framework for engine
 * systems in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#pragma once

#include "error_codes.hpp"
#include "object.hpp"

namespace SquirrelEngine {
class Engine;

/**
 * @brief Base class for all engine systems in SquirrelEngine.
 */
class System : public Object {
public:
    /**
     * @brief Default constructor for System.
     */
    System() = default;

    /**
     * @brief Virtual destructor for System.
     */
    virtual ~System() = default;

    /**
     * @brief Initializes the system with a pointer to the owning engine.
     * @param t_owner Pointer to the Engine that owns this system.
     * @return StartupErrors indicating success or failure.
     */
    virtual StartupErrors initialize( Engine* t_owner );

    /**
     * @brief Updates the system.
     * @param delta Time elapsed since last update.
     */
    virtual void update( const float ) {}

    /**
     * @brief Shuts down the system and performs cleanup.
     */
    virtual void shutdown() {}

protected:
    Engine* owner; //!< Pointer to the owning Engine.
};

} // namespace SquirrelEngine

#endif
