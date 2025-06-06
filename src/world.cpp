
#include "world.hpp"
#include "entity.hpp"

namespace SquirrelEngine {

World::World() {}

World::~World() {}

Entity* World::createEntity( const std::string name, const uint32_t id ) {
    m_entitesList.push_back( std::make_unique< Entity >( id, name ) );

    Entity* newEntity = m_entitesList.back().get();
    m_entitesMap.insert( { name, newEntity } );

    return newEntity;
}

Entity* World::findEntity( const uint32_t id ) {
    return m_entitesList.at( id ).get();
}

Entity* World::findEntity( const std::string name ) {
    return m_entitesMap.at( name );
}

void World::removeEntity( const Entity* entity ) {
    m_entitesMap.erase( entity->name );
    m_entitesList.erase( m_entitesList.begin() + entity->id );
}

std::vector< std::unique_ptr< Entity > >& World::getEntityList() {
    return m_entitesList;
}

World* World::instance() {
    static World m_instance;
    return &m_instance;
}

} // namespace SquirrelEngine
