/**
 *
 * @file world.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the World class, which manages all entities and their
 * lifecycle in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "world.hpp"
#include "entity.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for World (private for singleton pattern).
 */
World::World() {}

/**
 * @brief Destructor for World.
 */
World::~World() {}

/**
 * @brief Creates a new entity.
 * @param name Optional name for the entity.
 * @param id Optional unique ID for the entity.
 * @return Pointer to the created Entity.
 */
Entity* World::createEntity( const std::string name, const uint32_t id ) {
    m_entitesList.push_back( std::make_unique< Entity >( id, name ) );

    Entity* newEntity = m_entitesList.back().get();
    m_entitesMap.insert( { name, newEntity } );

    return newEntity;
}

/**
 * @brief Finds an entity by its unique ID.
 * @param id The entity's unique ID.
 * @return Pointer to the found Entity, or nullptr if not found.
 */
Entity* World::findEntity( const uint32_t id ) {
    return m_entitesList.at( id ).get();
}

/**
 * @brief Finds an entity by its name.
 * @param name The entity's name.
 * @return Pointer to the found Entity, or nullptr if not found.
 */
Entity* World::findEntity( const std::string name ) {
    return m_entitesMap.at( name );
}

/**
 * @brief Removes an entity from the world.
 * @param entity Pointer to the entity to remove.
 */
void World::removeEntity( const Entity* entity ) {
    m_entitesMap.erase( entity->name );
    m_entitesList.erase( m_entitesList.begin() + entity->id );
}

/**
 * @brief Gets the list of all entities.
 * @return Reference to the vector of unique pointers to entities.
 */
std::vector< std::unique_ptr< Entity > >& World::getEntityList() {
    return m_entitesList;
}

/**
 * @brief Gets the singleton instance of the World.
 * @return Pointer to the World instance.
 */
World* World::instance() {
    static World m_instance;
    return &m_instance;
}

} // namespace SquirrelEngine
