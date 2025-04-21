
#include "core.hpp"
#include <memory>

namespace SquirrelEngine {

Engine::~Engine() {}

enum StartupErrors Engine::initialize() {
    m_systemContainer = std::make_unique< SystemContainer >();

    // Create essential systems
    m_systemContainer->addSystem( std::make_unique< Graphics >( this ) );
    m_systemContainer->addSystem( std::make_unique< TimeManager >( this ) );

    // Initialize each system that was created
    for ( auto& it : m_systemContainer->getSystemList() ) {
        const StartupErrors result = it.second->initialize();
        if ( result != SE_Success ) {
            return result;
        }
    }

    m_isRunning = true;

    return StartupErrors::SE_Success;
}

void Engine::update() {
    auto* timeManager = m_systemContainer->getSystem< TimeManager >();
    timeManager->resetLastTime();

    auto* graphicsInstance = m_systemContainer->getSystem< Graphics >();

    // Main update loop
    while ( m_isRunning ) {
        // Increment time values
        timeManager->increment();

        // TODO: update input

        // Fixed update loop
        while ( timeManager->needsFixedUpdate() ) {
            // TODO: call fixed update callbacks
        }

        // TODO: call non-fixed update callbacks

        // TODO: call render function
        graphicsInstance->render();
    }
}

void Engine::shutdown() {
    // TODO: shutdown each of the systems
}

void Engine::triggerShutdown() { m_isRunning = false; }

} // namespace SquirrelEngine
