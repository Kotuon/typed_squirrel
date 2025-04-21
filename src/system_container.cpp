
#include "core.hpp"

namespace SquirrelEngine {

SystemContainer::SystemContainer() {}

void SystemContainer::addSystem( std::unique_ptr< System > t_system ) {
    m_systems[t_system->getType()] = std::move( t_system );
}

std::unordered_map< enum SystemType, std::unique_ptr< System > >&
SystemContainer::getSystemList() {
    return m_systems;
}

} // namespace SquirrelEngine
