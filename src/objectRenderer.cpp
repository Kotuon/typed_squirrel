/**
 *
 * @file objectRenderer.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the ObjectRenderer class, which handles rendering of
 * entities in SquirrelEngine.
 * @date 2025-05-05
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "entity.hpp"
#include "objectRenderer.hpp"
#include "window.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for ObjectRenderer.
 */
ObjectRenderer::ObjectRenderer() {}

/**
 * @brief Renders all entities in the world by drawing their models and swapping
 * the window buffer.
 */
void ObjectRenderer::render() {
    World* world = World::instance();

    // TODO: update shaders

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    auto& entityList = world->getEntityList();
    for ( auto& entity : entityList ) {
        Model* model = entity->findComponent< Model >();
        if ( !model ) {
            continue;
        }

        model->draw();
    }

    // Swap buffer (may move later)
    Window* window = Engine::instance()->getWindowHandle();
    window->swapBuffer();
}

} // namespace SquirrelEngine
