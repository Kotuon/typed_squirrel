
#ifndef WORLD_EDITOR_HPP
#define WORLD_EDITOR_HPP
#pragma once

#include <memory>
#include <vector>

#include "system.hpp"

namespace SquirrelEngine {
class Entity;
class World;

class WorldEditor : public System {
public:
    WorldEditor();

    virtual StartupErrors initialize( Engine* t_owner );

    virtual void update();

private:
    void showObjects( std::vector< std::unique_ptr< Entity > >& entityList );
    void showComponents( Entity* entity );

    World* m_world;

    int m_selectedEntity = -1;
    int m_selectedComponent = -1;
};

} // namespace SquirrelEngine

#endif
