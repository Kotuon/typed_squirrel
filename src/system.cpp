/**
 *
 * @file system.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the System base class, which provides a framework for
 * engine systems in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <functional>

#include "engine.hpp"
#include "system.hpp"

namespace SquirrelEngine {

/**
 * @brief Initializes the system with a pointer to the owning engine.
 * @param t_owner Pointer to the Engine that owns this system.
 * @return StartupErrors indicating success or failure.
 */
StartupErrors System::initialize( Engine* t_owner ) {
    owner = t_owner;

    owner->addUpdateCallback(
        std::bind( &System::update, this, std::placeholders::_1 ) );

    return StartupErrors::SE_Success;
}

} // namespace SquirrelEngine
