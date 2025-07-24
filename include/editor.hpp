
#ifndef EDITOR_HPP
#define EDITOR_HPP
#pragma once

#include <functional>
#include <vector>

#include "system.hpp"

namespace SquirrelEngine {

class Editor : public System {
public:
    Editor();

    virtual StartupErrors initialize( Engine* t_owner );

    virtual void update( const float );

    virtual void render();

    template < typename TCallback >
    void addDisplayMenuCallback( TCallback&& callback ) {
        m_displayMenuCallbacks.push_back( callback );
    }

private:
    virtual void displayDockspace();
    virtual void displayMenuBar();

    std::vector< std::function< void() > > m_displayMenuCallbacks;

    bool isOpen = true;
};

} // namespace SquirrelEngine

#endif
