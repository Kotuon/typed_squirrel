/**
 *
 * @file eventSystem.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the EventSystem class, which manages event subscription and
 * publishing in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "eventSystem.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for Subscriber.
 */
EventSystem::Subscriber::Subscriber()
    : type( typeid( this ) ), listener( nullptr ), callback( nullptr ) {}

/**
 * @brief Constructs a Subscriber with type, listener, and callback.
 * @param t_type The type_index of the event.
 * @param t_listener Pointer to the listener object.
 * @param t_callback Callback function pointer.
 */
EventSystem::Subscriber::Subscriber( std::type_index t_type, Object* t_listener,
                                     EventHandlingCallback t_callback )
    : type( typeid( t_type ) ), listener( t_listener ), callback( t_callback ) {
}

} // namespace SquirrelEngine
