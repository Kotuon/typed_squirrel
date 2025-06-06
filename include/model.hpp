/**
 *
 * @file model.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Model class, which represents a renderable model
 * component in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <memory>

#include "component.hpp"

namespace SquirrelEngine {
class Mesh;

/**
 * @brief Represents a renderable model component.
 */
class Model : public Component {
public:
    /**
     * @brief Constructs a Model with the given parent entity.
     * @param t_parent Pointer to the parent Entity.
     */
    Model( Entity* t_parent );

    /**
     * @brief Destructor for Model.
     */
    ~Model();

    /**
     * @brief Initializes the mesh from a file.
     * @param filename The mesh file name.
     */
    void initMesh( const std::string& filename );

    /**
     * @brief Initializes the shader for this model.
     * @param vertName Vertex shader file name.
     * @param fragName Fragment shader file name.
     */
    void initShader( const std::string& vertName, const std::string& fragName );

    /**
     * @brief Draws the model.
     */
    void draw();

    /**
     * @brief Sets the mesh for this model.
     * @param t_mesh Pointer to the Mesh.
     */
    void setMesh( Mesh* t_mesh );

    /**
     * @brief Gets the mesh associated with this model.
     * @return Pointer to the Mesh.
     */
    Mesh* getMesh() const;

    /**
     * @brief Sets the render method (OpenGL primitive type).
     * @param t_renderMethod The render method (e.g., GL_TRIANGLES).
     */
    void setRenderMethod( GLuint t_renderMethod );

    /**
     * @brief Gets the render method (OpenGL primitive type).
     * @return The render method.
     */
    GLuint getRenderMethod() const;

private:
    std::unique_ptr< Mesh > m_mesh; //!< Pointer to the mesh.
    GLuint m_renderMethod; //!< OpenGL render method (e.g., GL_TRIANGLES).
};

} // namespace SquirrelEngine

#endif
