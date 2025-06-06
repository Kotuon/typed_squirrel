/**
 *
 * @file objectRenderer.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
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

namespace SquirrelEngine {

ObjectRenderer::ObjectRenderer() {}

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
}

} // namespace SquirrelEngine
