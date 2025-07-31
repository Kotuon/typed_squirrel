/**
 *
 * @file engine.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Engine class, which manages core systems, update loops,
 * and the main application flow for SquirrelEngine.
 * @date 2025-04-25
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.hpp"
#include <memory>

namespace SquirrelEngine {

/**
 * @brief Default constructor for Engine.
 */
Engine::Engine() {}

/**
 * @brief Virtual destructor for Engine.
 */
Engine::~Engine() {}

/**
 * @brief Starts all essential systems for the engine.
 * @return StartupErrors indicating success or failure.
 */
enum StartupErrors Engine::initialize() {
    m_window = std::make_unique< Window >();
    m_window->create( "SquirrelEngine", 1280, 720, false );

    if ( !createSystem< TimeManager >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< EventSystem >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( InputSystem* inputSystem = createSystem< InputSystem >() ) {
        Keyboard* keyboard = inputSystem->createInputDevice< Keyboard >();
        keyboard->initialize();

        Mouse* mouse = inputSystem->createInputDevice< Mouse >();
        mouse->initialize();

    } else {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< ObjectRenderer >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< Editor >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }
    if ( !createSystem< WorldEditor >() ) {
        return StartupErrors::SE_SystemFailedInit;
    }

    return StartupErrors::SE_Success;
}

/**
 * @brief Moves the camera based on input and delta time.
 * @param cameraC Pointer to the CameraComponent.
 * @param timeManager Pointer to the TimeManager system.
 * @param inputSystem Pointer to the InputSystem.
 */
static void moveCamera( Entity* camera, TimeManager* timeManager,
                        InputSystem* inputSystem ) {
    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    if ( !inputSystem->getActionState( "enable camera movement" ) ) {
        mouse->setCursorMode( GLFW_CURSOR_NORMAL );
        return;
    }
    mouse->setCursorMode( GLFW_CURSOR_DISABLED );

    CameraComponent* cCamera = camera->findComponent< CameraComponent >();

    const float speed = 5.f;

    camera->transform.move( cCamera->forwardVector() *
                            timeManager->getDeltaTime() * speed *
                            inputSystem->getActionState( "move forward" ) );

    camera->transform.move( cCamera->forwardVector() *
                            timeManager->getDeltaTime() * -speed *
                            inputSystem->getActionState( "move backward" ) );

    camera->transform.move( cCamera->rightVector() *
                            timeManager->getDeltaTime() * -speed *
                            inputSystem->getActionState( "move left" ) );

    camera->transform.move( cCamera->rightVector() *
                            timeManager->getDeltaTime() * speed *
                            inputSystem->getActionState( "move right" ) );

    camera->transform.move( cCamera->upVector() * timeManager->getDeltaTime() *
                            speed * inputSystem->getActionState( "move up" ) );

    camera->transform.move( cCamera->upVector() * timeManager->getDeltaTime() *
                            -speed *
                            inputSystem->getActionState( "move down" ) );

    vector2 mouseDelta = mouse->getCursorDelta();

    CameraComponent* cameraC = camera->findComponent< CameraComponent >();

    cameraC->addPitch( glm::radians( cameraC->getSensitivity() * -mouseDelta.y *
                                     timeManager->getDeltaTime() ) );

    cameraC->addYaw( glm::radians( cameraC->getSensitivity() * -mouseDelta.x *
                                   timeManager->getDeltaTime() ) );
}

/**
 * @brief Handles updates for all systems in engine.
 */
void Engine::update() {
    TimeManager* timeManager = getSystem< TimeManager >();
    InputSystem* inputSystem = getSystem< InputSystem >();
    ObjectRenderer* objRenderer = getSystem< ObjectRenderer >();
    Editor* editor = getSystem< Editor >();

    glfwSetInputMode( m_window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );

    World* world = World::instance();
    Entity* camera = world->findEntity( "Main camera" );

    // Main update loop
    while ( !m_window->isClosing() ) {
        // Increment time values
        timeManager->increment();

        // Gather inputs
        m_window->pollEvents();

        if ( inputSystem->getActionState( "close window" ) ) {
            glfwSetWindowShouldClose( m_window->getHandle(), GL_TRUE );
        }

        moveCamera( camera, timeManager, inputSystem );

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
        editor->render();

        m_window->swapBuffer();

        // Don't use whole cpu
        timeManager->sleep( 1 );
    }
}

/**
 * @brief Properly shuts all systems down on engine close.
 */
void Engine::shutdown() {
    // TODO: shutdown each of the systems
}

/**
 * @brief Get the Window Handle object.
 * @return Pointer to the window handle.
 */
Window* Engine::getWindowHandle() { return m_window.get(); }

/**
 * @brief Get the singleton instance of the Engine.
 * @return Pointer to the Engine instance.
 */
Engine* Engine::instance() {
    static Engine engineInstance;
    return &engineInstance;
}

} // namespace SquirrelEngine