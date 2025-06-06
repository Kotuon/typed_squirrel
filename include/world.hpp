
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

class World : public Object {
public:
    ~World();

    Entity* createEntity( const std::string name = "", const uint32_t id = 0 );

    Entity* findEntity( const uint32_t id );
    Entity* findEntity( const std::string name );

    void removeEntity( const Entity* entity );

    std::vector<std::unique_ptr<Entity>>& getEntityList();

    static World* instance();

private:
    World();

protected:
    std::vector< std::unique_ptr< Entity > > m_entitesList;
    std::unordered_map< std::string, Entity* > m_entitesMap;
};

} // namespace SquirrelEngine

#endif
