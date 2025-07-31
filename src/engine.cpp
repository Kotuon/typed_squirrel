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

    // Texture test ////////////////////////////////////////////////////////////
    int max_compute_work_group_count[3];
    int max_compute_work_group_size[3];
    int max_compute_work_group_invocations;

    for ( int idx = 0; idx < 3; idx++ ) {
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_COUNT, idx,
                         &max_compute_work_group_count[idx] );
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_SIZE, idx,
                         &max_compute_work_group_size[idx] );
    }
    glGetIntegerv( GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
                   &max_compute_work_group_invocations );

    Program quad( "shaders/quad.vert", "shaders/quad.frag" );
    glUseProgram( quad.getHandle() );
    glUniform1i( quad.getLocation( "tex" ), 0 );

    Program compute( "shaders/test.comp" );

    const unsigned TEXTURE_WIDTH = 1000, TEXTURE_HEGIHT = 1000;
    unsigned texture;
    glGenTextures( 1, &texture );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEGIHT,
                  0, GL_RGBA, GL_FLOAT, NULL );

    glBindImageTexture( 0, texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );
    ////////////////////////////////////////////////////////////////////////////

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

        // Compute test ////////////////////////////////////////////////////////
        glUseProgram( compute.getHandle() );
        glUniform1f( compute.getLocation( "t" ), timeManager->getTotalTime() );
        glDispatchCompute( TEXTURE_WIDTH / 10, TEXTURE_HEGIHT / 10, 1 );
        glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
        ////////////////////////////////////////////////////////////////////////
        // TODO: call render function
        ///////////// objRenderer->render();
        // Quad test ///////////////////////////////////////////////////////////
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram( quad.getHandle() );
        static unsigned quadVAO = 0;
        static unsigned quadVBO;
        if ( quadVAO == 0 ) {
            float quadVertices[]{
                -1.f, 1.f, 0.f, 0.f, 1.f, -1.f, -1.f, 0.f, 0.f, 0.f,
                1.f,  1.f, 0.f, 1.f, 1.f, 1.f,  -1.f, 0.f, 1.f, 0.f,
            };

            glGenVertexArrays( 1, &quadVAO );
            glGenBuffers( 1, &quadVBO );
            glBindVertexArray( quadVAO );
            glBindBuffer( GL_ARRAY_BUFFER, quadVBO );
            glBufferData( GL_ARRAY_BUFFER, sizeof( quadVertices ),
                          &quadVertices, GL_STATIC_DRAW );
            glEnableVertexAttribArray( 0 );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE,
                                   5 * sizeof( float ), ( void* )0 );
            glEnableVertexAttribArray( 1 );
            glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE,
                                   5 * sizeof( float ),
                                   ( void* )( 3 * sizeof( float ) ) );
        }
        glBindVertexArray( quadVAO );
        glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
        glBindVertexArray( 0 );
        ////////////////////////////////////////////////////////////////////////
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