
#ifndef SYSTEM_CONTAINER_HPP
#define SYSTEM_CONTAINER_HPP
#pragma once

#include <memory>
#include <unordered_map>

#include "module.hpp"

namespace SquirrelEngine {

class ModuleContainer {
public:
    ModuleContainer();

    /**
     * @brief Add system to list
     *
     * @param t_component
     */
    void addModule( std::unique_ptr< Module > t_module );

    template < typename T > T* getModule() {
        // Search for system
        auto found = m_modules.find( T::getType() );

        // System doesn't exist
        if ( found == m_modules.end() ) {
            return nullptr;
        }

        return ( T* )found->second.get();
    }

    std::unordered_map< enum ModuleType, std::unique_ptr< Module > >&
    getModuleList();

private:
    std::unordered_map< enum ModuleType, std::unique_ptr< Module > >
        m_modules; //!< List of all the systems managed by container
};

} // namespace SquirrelEngine

#endif
