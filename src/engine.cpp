/**
 *
 * @file engine.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-04-25
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.hpp"
#include <memory>

namespace SquirrelEngine {

Engine::Engine() {}

Engine::~Engine() {}

enum StartupErrors Engine::initialize() {
    m_window = std::make_unique< Window >();

    if ( !createSystem< TimeManager >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< EventSystem >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< ObjectRenderer >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }

    return StartupErrors::SE_Success;
}

static void moveCamera( CameraComponent* cameraC, TimeManager* timeManager,
                        InputSystem* inputSystem ) {

    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    if ( !inputSystem->getActionState( "enable camera movement" ) ) {
        mouse->setCursorMode( GLFW_CURSOR_NORMAL );
        return;
    }
    mouse->setCursorMode( GLFW_CURSOR_DISABLED );

    const float speed = 5.f;

    cameraC->transform.move( cameraC->transform.forwardVector() *
                             timeManager->getDeltaTime() * speed *
                             inputSystem->getActionState( "move forward" ) );

    cameraC->transform.move( cameraC->transform.forwardVector() *
                             timeManager->getDeltaTime() * -speed *
                             inputSystem->getActionState( "move backward" ) );

    cameraC->transform.move( cameraC->transform.rightVector() *
                             timeManager->getDeltaTime() * -speed *
                             inputSystem->getActionState( "move left" ) );

    cameraC->transform.move( cameraC->transform.rightVector() *
                             timeManager->getDeltaTime() * speed *
                             inputSystem->getActionState( "move right" ) );

    cameraC->transform.move( cameraC->transform.upVector() *
                             timeManager->getDeltaTime() * speed *
                             inputSystem->getActionState( "move up" ) );

    cameraC->transform.move( cameraC->transform.upVector() *
                             timeManager->getDeltaTime() * -speed *
                             inputSystem->getActionState( "move down" ) );

    vector2 mouseDelta = mouse->getCursorDelta();

    cameraC->rotatePitch(
        glm::radians( cameraC->getSensitivity() * -mouseDelta.y *
                      timeManager->getDeltaTime() ) );

    cameraC->rotateYaw(
        glm::radians( cameraC->getSensitivity() * -mouseDelta.x *
                      timeManager->getDeltaTime() ) );
}

void Engine::update() {
    TimeManager* timeManager = getSystem< TimeManager >();
    InputSystem* inputSystem = getSystem< InputSystem >();
    ObjectRenderer* objRenderer = getSystem< ObjectRenderer >();

    glfwSetInputMode( m_window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );

    World* world = World::instance();
    CameraComponent* cameraC =
        world->findEntity( "Main camera" )->findComponent< CameraComponent >();

    // Main update loop
    while ( !m_window->isClosing() ) {
        // Increment time values
        timeManager->increment();

        // Gather inputs
        m_window->pollEvents();

        if ( inputSystem->getActionState( "close window" ) ) {
            glfwSetWindowShouldClose( m_window->getHandle(), GL_TRUE );
        }

        moveCamera( cameraC, timeManager, inputSystem );

        // Fixed update loop
        while ( timeManager->needsFixedUpdate() ) {
            // Fixed update callbacks
            for ( auto& func : fixedUpdateCallbacks ) {
                func();
            }
        }

        // Non-fixed update callbacks
        for ( auto& func : updateCallbacks ) {
            func( timeManager->getDeltaTime() );
        }

        // TODO: call render function
        objRenderer->render();

        // Don't use whole cpu
        timeManager->sleep( 1 );
    }
}

void Engine::shutdown() {
    // TODO: shutdown each of the systems
}

Window* Engine::getWindowHandle() { return m_window.get(); }

Engine* Engine::instance() {
    static Engine engineInstance;
    return &engineInstance;
}

} // namespace SquirrelEngine