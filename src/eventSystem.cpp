
#include "eventSystem.hpp"

namespace SquirrelEngine {

EventSystem::Subscriber::Subscriber()
    : type( typeid( this ) ), listener( nullptr ), callback( nullptr ) {}

EventSystem::Subscriber::Subscriber( std::type_index t_type, Object* t_listener,
                                     EventHandlingCallback t_callback )
    : type( typeid( t_type ) ), listener( t_listener ), callback( t_callback ) {
}

} // namespace SquirrelEngine
