
#include "core.hpp"

namespace SquirrelEngine {

ModuleContainer::ModuleContainer() {}

void ModuleContainer::addModule( std::unique_ptr< Module > t_module ) {
    m_modules[t_module->getType()] = std::move( t_module );
}

std::unordered_map< enum ModuleType, std::unique_ptr< Module > >&
ModuleContainer::getModuleList() {
    return m_modules;
}

} // namespace SquirrelEngine
