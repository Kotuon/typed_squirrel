/**
 *
 * @file entity.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Entity class, which represents game objects and manages
 * their components in SquirrelEngine.
 * @date 2025-06-06
 *
 */

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
    /**
     * @brief Default constructor for Entity.
     */
    Entity() : id( 0 ) {}

    /**
     * @brief Constructs an Entity with a given ID.
     * @param t_id The entity's unique identifier.
     */
    Entity( const uint32_t t_id ) : id( t_id ) {}

    /**
     * @brief Constructs an Entity with a given ID and name.
     * @param t_id The entity's unique identifier.
     * @param t_name The entity's name.
     */
    Entity( const uint32_t t_id, const std::string t_name )
        : id( t_id ), name( t_name ) {}

    /**
     * @brief Default virtual destructor for Entity.
     */
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

    /**
     * @brief The unique identifier for this entity.
     */
    uint32_t id;

    /**
     * @brief The name of this entity.
     */
    std::string name;

    /**
     * @brief The transform associated with this entity.
     */
    Transform transform;

protected:
    /**
     * @brief The list of components attached to this entity.
     */
    std::vector< std::unique_ptr< Component > > m_components;
};

} // namespace SquirrelEngine

#endif
