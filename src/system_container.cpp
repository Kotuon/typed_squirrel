
#include "core.hpp"

namespace SquirrelEngine {

SystemContainer::SystemContainer() {}

void SystemContainer::addComponent( std::unique_ptr< System > t_component ) {
    m_systems[t_component->getType()] = std::move( t_component );
}

} // namespace SquirrelEngine
