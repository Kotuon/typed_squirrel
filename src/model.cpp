/**
 *
 * @file model.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Model class, which represents a renderable model
 * component in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "core.hpp"
#include "mesh.hpp"
#include "model.hpp"

namespace SquirrelEngine {

/**
 * @brief Constructs a Model with the given parent entity.
 * @param t_parent Pointer to the parent Entity.
 */
Model::Model( Entity* t_parent )
    : Component( t_parent ), m_mesh( nullptr ), m_renderMethod( GL_TRIANGLES ) {
}

/**
 * @brief Destructor for Model.
 */
Model::~Model() {}

/**
 * @brief Initializes the mesh from a file.
 * @param filename The mesh file name.
 */
void Model::initMesh( const std::string& filename ) {
    m_mesh = std::make_unique< Mesh >( this );
    m_mesh->load( filename );
}

/**
 * @brief Initializes the shader for this model.
 * @param vertName Vertex shader file name.
 * @param fragName Fragment shader file name.
 */
void Model::initShader( const std::string& vertName,
                        const std::string& fragName ) {
    if ( !m_mesh ) {
        Trace::message( "Failed to make shader: No mesh" );
        return;
    }

    m_mesh->loadShader( vertName, fragName );
}

/**
 * @brief Draws the model.
 */
void Model::draw() { m_mesh->draw(); }

/**
 * @brief Sets the mesh for this model.
 * @param t_mesh Pointer to the Mesh.
 */
void Model::setMesh( Mesh* t_mesh ) {
    m_mesh = std::make_unique< Mesh >( t_mesh );
}

/**
 * @brief Gets the mesh associated with this model.
 * @return Pointer to the Mesh.
 */
Mesh* Model::getMesh() const { return m_mesh.get(); }

/**
 * @brief Sets the render method (OpenGL primitive type).
 * @param t_renderMethod The render method (e.g., GL_TRIANGLES).
 */
void Model::setRenderMethod( GLuint t_renderMethod ) {
    m_renderMethod = t_renderMethod;
}

/**
 * @brief Gets the render method (OpenGL primitive type).
 * @return The render method.
 */
GLuint Model::getRenderMethod() const { return m_renderMethod; }

} // namespace SquirrelEngine
