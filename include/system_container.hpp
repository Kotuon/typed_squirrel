
#ifndef SYSTEM_CONTAINER_HPP
#define SYSTEM_CONTAINER_HPP
#pragma once

#include <memory>
#include <unordered_map>

#include "system.hpp"

namespace SquirrelEngine {

class SystemContainer {
public:
    SystemContainer();

    void addComponent( std::unique_ptr< System > t_component );

    template < typename T > T* getSystem() {
        // Search for system
        auto found = m_systems.find( T::getType() );

        // System doesn't exist
        if ( found == m_systems.end() ) {
            return nullptr;
        }

        return ( T* )found->second.get();
    }

private:
    std::unordered_map< enum SystemType, std::unique_ptr< System > >
        m_systems; //!< List of all the systems managed by container
};

} // namespace SquirrelEngine

#endif
