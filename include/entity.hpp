
#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "object.hpp"
#include "transform.hpp"
#include "component.hpp"

namespace SquirrelEngine {
class Entity : public Object {
public:
    Entity() : id( 0 ) {}
    Entity( const uint32_t t_id ) : id( t_id ) {}
    Entity( const uint32_t t_id, const std::string t_name )
        : id( t_id ), name( t_name ) {}

    ~Entity() = default;

    /**
     * @brief Create a Component object on this entity
     *
     * @tparam T
     * @return T*
     */
    template < class T > T* createComponent() {
        m_components.emplace_back( std::make_unique< T >( this ) );
        return dynamic_cast< T* >( m_components.back().get() );
    }

    /**
     * @brief Returns first component of specified type
     *
     * @tparam T
     * @return T*
     */
    template < class T > T* findComponent() {
        for ( auto it = m_components.begin(); it != m_components.end(); ++it ) {
            T* obj = dynamic_cast< T* >( it->get() );
            if ( obj ) {
                return obj;
            }
        }

        return nullptr;
    }

    /**
     * @brief Returns all components of specified type
     *
     * @tparam T
     * @return std::vector<T*>
     */
    template < class T > std::vector< T* > findComponents() {
        std::vector< T* > returnList;

        for ( auto it = m_components.begin(); it != m_components.end(); ++it ) {
            T* obj = dynamic_cast< T* >( it->get() );
            if ( obj ) {
                returnList.push_back( obj );
            }
        }

        return returnList;
    }

    /**
     * @brief Removes given component
     *
     * @param component
     */
    void removeComponent( const Component* component ) {
        for ( auto it = m_components.begin(); it <= m_components.end(); ++it ) {
            if ( it->get() == component ) {
                m_components.erase( it );
                return;
            }
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
