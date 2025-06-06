/**
 *
 * @file engine.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Class for handing startup, update, and shutdown of engine
 * @date 2025-04-20
 *
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP
#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "error_codes.hpp"
#include "object.hpp"

#include "system.hpp"

#include "utils/trace.hpp"

namespace SquirrelEngine {
// Forward declarations of enums
enum StartupErrors : unsigned;

// Forward declarations of classes
class Window;

class Engine : public Object {
public:
    virtual ~Engine();

    /**
     * @brief Starts all essential systems for the engine
     *
     * @return true Successfully started engine
     * @return false Failed to start engine
     */
    enum StartupErrors initialize();

    /**
     * @brief Handles updates for all systems in engine
     *
     */
    void update();

    /**
     * @brief Properly shuts all systems down on engine close
     *
     */
    void shutdown();

    /**
     * @brief Get the Window Handle object
     *
     * @return Window*
     */
    Window* getWindowHandle();

    /**
     * @brief Create a System object owned by the engine
     *
     * @tparam T
     * @return true
     * @return false
     */
    template < class T > T* createSystem() {
        m_systems.emplace_back( std::make_unique< T >() );
        auto& system = m_systems.back();

        if ( system->initialize( this ) != StartupErrors::SE_Success ) {
            return nullptr;
        }

        return dynamic_cast< T* >( system.get() );
    }

    /**
     * @brief Get the System object
     *
     * @tparam T
     * @return T*
     */
    template < class T > T* getSystem() {
        for ( auto it = m_systems.begin(); it != m_systems.end(); ++it ) {
            T* system = dynamic_cast< T* >( ( *it ).get() );
            if ( system ) {
                return system;
            }
        }

        return nullptr;
    }

    /**
     * @brief Adds fixed update function to call
     *
     * @tparam TCallback
     * @param callback
     */
    template < typename TCallback >
    void addFixedUpdateCallback( TCallback&& callback ) {
        fixedUpdateCallbacks.insert( fixedUpdateCallbacks.begin(), callback );
    }

    /**
     * @brief Adds regular update function to call
     *
     * @tparam TCallback
     * @param callback
     */
    template < typename TCallback >
    void addUpdateCallback( TCallback&& callback ) {
        updateCallbacks.insert( updateCallbacks.begin(), callback );
    }

    static Engine* instance();

private:
    Engine();

    std::vector< std::function< void( const float ) > > updateCallbacks;
    std::vector< std::function< void() > > fixedUpdateCallbacks;

    std::vector< std::unique_ptr< System > > m_systems;
    std::unique_ptr< Window > m_window;
};

template < class T > T* getSystem() {
    Engine* engineInstance = Engine::instance();
    return engineInstance->getSystem< T >();
}

} // namespace SquirrelEngine
#endif