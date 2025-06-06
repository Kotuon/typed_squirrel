/**
 *
 * @file eventSystem.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the EventSystem class, which manages event subscription and
 * publishing in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP
#pragma once

#include <memory>
#include <typeindex>
#include <vector>

#include "system.hpp"

namespace SquirrelEngine {
class Event;

/**
 * @brief Callback function type for event handling.
 */
typedef void ( *EventHandlingCallback )( Object* obj, Event* event );

/**
 * @brief The EventSystem class manages event subscription and publishing.
 */
class EventSystem : public System {
public:
    /**
     * @brief Default constructor for EventSystem.
     */
    EventSystem() = default;

    /**
     * @brief Default destructor for EventSystem.
     */
    ~EventSystem() = default;

    /**
     * @brief Subscriber class for event listeners.
     */
    class Subscriber {
    public:
        /**
         * @brief Default constructor for Subscriber.
         */
        Subscriber();

        /**
         * @brief Constructs a Subscriber with type, listener, and callback.
         * @param t_type The type_index of the event.
         * @param t_listener Pointer to the listener object.
         * @param t_callback Callback function pointer.
         */
        Subscriber( std::type_index t_type, Object* t_listener,
                    EventHandlingCallback t_callback );

        /**
         * @brief Default destructor for Subscriber.
         */
        ~Subscriber() = default;

        std::type_index type;           //!< Type of event to listen for.
        Object* listener;               //!< Pointer to the listener object.
        EventHandlingCallback callback; //!< Callback function pointer.
    };

    /**
     * @brief Subscribe an object to a specific event type.
     * @tparam T Event type to subscribe to.
     * @param t_listener Pointer to the listener object.
     * @param t_callback Callback function pointer.
     */
    template < class T >
    void subscribe( Object* t_listener, EventHandlingCallback t_callback ) {
        m_subscribers.emplace_back( std::make_unique< Subscriber >(
            typeid( T ), t_listener, t_callback ) );
    }

    /**
     * @brief Publish an event to all subscribers of the event type.
     * @tparam EventType Type of the event to publish.
     * @param event Pointer to the event object.
     */
    template < typename EventType > void publish( EventType* event ) {
        std::type_index searchType = typeid( EventType );

        for ( auto it = m_subscribers.begin(); it != m_subscribers.end();
              ++it ) {
            auto* current = ( *it ).get();

            if ( searchType != current->type ) continue;

            current->callback( current->listener, event );
        }
    }

protected:
    std::vector< std::unique_ptr< Subscriber > >
        m_subscribers; //!< List of event subscribers.
};

} // namespace SquirrelEngine

#endif
