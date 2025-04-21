
#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "object.hpp"
#include "transform.hpp"

namespace SquirrelEngine {
class Component;

class Entity : public Object {
public:
    Entity();
    ~Entity();

    template < class T > T* createComponent() {
        m_components.emplace_back( std::make_unique< T >() );
        return m_components.back().get();
    }

    template < class T > T* findComponent() {
        for ( auto it = m_components.begin(); it != m_components.end(); ++it ) {
            T* obj = dynamic_cast< T* >( it->get() );
            if ( obj ) {
                return object;
            }
        }

        return nullptr;
    }

    void removeComponent( Component* component ) {
        auto it =
            std::find( m_components.begin(), m_components.end(), component );
        if ( it != m_components.end() ) {
            m_components.erase( it );
        }
    }

    uint32_t id;
    std::string name;

    Transform transform;

protected:
    std::vector< std::unique_ptr< Component > > m_components;
};

} // namespace SquirrelEngine

#endif
