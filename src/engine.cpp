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

    const float speed = 10.f;

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
struct PerFrameData {
    matrix4 view;
    matrix4 proj;
    vector4 cameraPos;
};

void Engine::update( World* world ) {
    TimeManager* timeManager = getSystem< TimeManager >();
    InputSystem* inputSystem = getSystem< InputSystem >();

    glfwSetInputMode( m_window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );

    CameraComponent* cameraC =
        world->findEntity( "Main camera" )->findComponent< CameraComponent >();

    Program baseProgram( "shaders/base.vert", "shaders/base.frag" );

    Model* model = ModelManager::instance().getModel(
        "models/cube.obj", GL_TRIANGLES, baseProgram.getHandle(), false );

    const float scale = 0.5f;

    matrix4 matrix = glm::scale( glm::mat4( 1.f ), { scale, scale, scale } );

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
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glUseProgram( model->getShader() );

        glUniformMatrix4fv( glGetUniformLocation( model->getShader(), "model" ),
                            1, GL_FALSE, &matrix[0][0] );

        glUniformMatrix4fv( glGetUniformLocation( model->getShader(), "view" ),
                            1, GL_FALSE, &cameraC->viewMatrix()[0][0] );
        glUniformMatrix4fv(
            glGetUniformLocation( model->getShader(), "projection" ), 1,
            GL_FALSE, &cameraC->projectionMatrix()[0][0] );

        glBindVertexArray( model->getMesh()->VAO );
        glDrawArrays( model->getRenderMethod(), 0,
                      model->getMesh()->NumVertices );

        glUseProgram( 0 );
        glBindVertexArray( 0 );

        // Swap buffer (may move later)
        m_window->swapBuffer();

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