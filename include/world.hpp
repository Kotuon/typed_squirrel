/**
 *
 * @file world.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the World class, which manages all entities and their
 * lifecycle in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef WORLD_HPP
#define WORLD_HPP
#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "object.hpp"

namespace SquirrelEngine {
// Class forward declaration
class Entity;

/**
 * @brief Manages all entities and their lifecycle in the engine.
 */
class World : public Object {
public:
    /**
     * @brief Destructor for World.
     */
    ~World();

    /**
     * @brief Creates a new entity.
     * @param name Optional name for the entity.
     * @param id Optional unique ID for the entity.
     * @return Pointer to the created Entity.
     */
    Entity* createEntity( const std::string name = "", const uint32_t id = 0 );

    /**
     * @brief Finds an entity by its unique ID.
     * @param id The entity's unique ID.
     * @return Pointer to the found Entity, or nullptr if not found.
     */
    Entity* findEntity( const uint32_t id );

    /**
     * @brief Finds an entity by its name.
     * @param name The entity's name.
     * @return Pointer to the found Entity, or nullptr if not found.
     */
    Entity* findEntity( const std::string name );

    /**
     * @brief Removes an entity from the world.
     * @param entity Pointer to the entity to remove.
     */
    void removeEntity( const Entity* entity );

    /**
     * @brief Gets the list of all entities.
     * @return Reference to the vector of unique pointers to entities.
     */
    std::vector< std::unique_ptr< Entity > >& getEntityList();

    /**
     * @brief Gets the singleton instance of the World.
     * @return Pointer to the World instance.
     */
    static World* instance();

private:
    /**
     * @brief Private constructor for singleton pattern.
     */
    World();

protected:
    std::vector< std::unique_ptr< Entity > >
        m_entitesList; //!< List of all entities.
    std::unordered_map< std::string, Entity* >
        m_entitesMap; //!< Map of entity names to pointers.
};

} // namespace SquirrelEngine

#endif
