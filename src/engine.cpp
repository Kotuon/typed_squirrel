
#include "core.hpp"
#include <memory>

namespace SquirrelEngine {

Engine::~Engine() {}

enum StartupErrors Engine::initialize() {
    m_systemContainer = std::make_unique< SystemContainer >();

    m_systemContainer->addComponent( std::make_unique< Graphics >( this ) );
    m_systemContainer->addComponent( std::make_unique< TimeManager >( this ) );
    m_isRunning = true;

    return StartupErrors::SE_Success;
}

void Engine::update() {
    auto* timeManager = m_systemContainer->getSystem< TimeManager >();
    timeManager->resetLastTime();

    // Main update loop
    while ( m_isRunning ) {
        // Increment time values
        timeManager->update();

        // TODO: update input

        // Fixed update loop
        while ( timeManager->needsFixedUpdate() ) {
            // TODO: call fixed update callbacks
        }

        // TODO: call non-fixed update callbacks

        // TODO: call render function
    }
}

void Engine::shutdown() {
    // TODO: shutdown each of the systems
}

} // namespace SquirrelEngine
