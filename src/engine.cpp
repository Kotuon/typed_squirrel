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

    return StartupErrors::SE_Success;
}

void Engine::update( World* world ) {
    TimeManager* timeManager = getSystem< TimeManager >();
    ShaderManager* shaderManager = getSystem< ShaderManager >();

    CameraComponent* cameraC =
        world->findEntity( "Main camera" )->findComponent< CameraComponent >();

    Model* model = ModelManager::instance().getModel(
        "models/cube.obj", GL_TRIANGLES,
        shaderManager->getShader( "shaders/base_vertex.glsl",
                                  "shaders/base_fragment.glsl" ),
        false );

    const float scale = 20.f;

    matrix4 matrix = glm::scale( glm::mat4( 1.f ), { scale, scale, scale } );

    // unsigned gridShader =
    //     shaderManager->getShader( "shaders/grid.vert", "shaders/grid.frag" );

    // Main update loop
    while ( !m_window->isClosing() ) {
        // Increment time values
        timeManager->increment();

        // Gather inputs
        m_window->pollEvents();

        // Fixed update loop
        while ( timeManager->needsFixedUpdate() ) {
            // Fixed update callbacks
            for ( auto& func : fixedUpdateCallbacks ) {
                func();
            }
        }

        // Non-fixed update callbacks
        for ( auto& func : updateCallbacks ) {
            func();
        }

        // TODO: call render function
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_STENCIL_BUFFER_BIT );

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

} // namespace SquirrelEngine