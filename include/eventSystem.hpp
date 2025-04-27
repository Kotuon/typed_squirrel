
#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP
#pragma once

#include <memory>
#include <typeindex>
#include <vector>

#include "system.hpp"

namespace SquirrelEngine {
class Event;

typedef void ( *EventHandlingCallback )( Object* obj, Event* event );

class EventSystem : public System {
public:
    EventSystem() = default;
    ~EventSystem() = default;

    class Subscriber {
    public:
        Subscriber();
        Subscriber( std::type_index t_type, Object* t_listener,
                    EventHandlingCallback t_callback );
        ~Subscriber() = default;

        std::type_index type;
        Object* listener;
        EventHandlingCallback callback;
    };

    template < class T >
    void subscribe( Object* t_listener, EventHandlingCallback t_callback ) {
        m_subscribers.emplace_back( std::make_unique< Subscriber >(
            typeid( T ), t_listener, t_callback ) );
    }

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
    std::vector< std::unique_ptr< Subscriber > > m_subscribers;
};

} // namespace SquirrelEngine

#endif
