/**
 *
 * @file mesh.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Mesh class, which represents a renderable mesh and its
 * associated data in SquirrelEngine.
 * @date 2025-05-05
 *
 */

#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>

#include "math_types.hpp"
#include "object.hpp"

namespace SquirrelEngine {
class Model;
class Program;

/**
 * @brief Structure representing a single vertex.
 */
struct Vertex {
    /**
     * @brief Constructs a Vertex with position, normal, and uv.
     * @param position_ Vertex position.
     * @param normal_ Vertex normal.
     * @param uv_ Vertex texture coordinates.
     */
    Vertex( vector3 position_, vector3 normal_, vector2 uv_ )
        : position( position_ ), normal( normal_ ), uv( uv_ ) {}

    vector3 position; //!< Vertex position.
    vector3 normal;   //!< Vertex normal.
    vector2 uv;       //!< Vertex texture coordinates.
};

/**
 * @brief Represents a renderable mesh and its associated data.
 */
class Mesh : public Object {
public:
    /**
     * @brief Default constructor for Mesh.
     */
    Mesh();

    /**
     * @brief Copy constructor for Mesh.
     * @param other Mesh to copy from.
     */
    Mesh( const Mesh& other );

    /**
     * @brief Copy constructor from pointer for Mesh.
     * @param other Pointer to Mesh to copy from.
     */
    Mesh( const Mesh* other );

    /**
     * @brief Constructs a Mesh with a given Model.
     * @param t_model Pointer to the Model.
     */
    Mesh( Model* t_model );

    /**
     * @brief Destructor for Mesh.
     */
    ~Mesh();

    /**
     * @brief Loads mesh data from a model file.
     * @param t_modelName Name of the model file.
     * @return true if loaded successfully, false otherwise.
     */
    bool load( std::string t_modelName );

    /**
     * @brief Draws the mesh.
     */
    void draw();

    /**
     * @brief Sets the shader program for this mesh.
     * @param t_shader Pointer to the shader Program.
     */
    void setShader( Program* t_shader );

    /**
     * @brief Gets the shader program associated with this mesh.
     * @return Pointer to the shader Program.
     */
    const Program* getShader() const;

    /**
     * @brief Loads and sets the shader from vertex and fragment shader files.
     * @param vertName Vertex shader filename.
     * @param fragName Fragment shader filename.
     */
    void loadShader( const std::string& vertName, const std::string& fragName );

    /**
     * @brief Gets the model name associated with this mesh.
     * @return The model name as a string.
     */
    std::string getModelName() const;

private:
    /**
     * @brief Reads mesh data from a model file.
     * @param t_modelName Name of the model file.
     * @return true if read successfully, false otherwise.
     */
    bool read( std::string t_modelName );

    /**
     * @brief Inserts vertex data from parsed model data.
     * @param data Array of strings containing vertex data.
     * @param v Vector of positions.
     * @param vt Vector of texture coordinates.
     * @param vn Vector of normals.
     */
    void insertData( char* data[3], std::vector< vector3 >& v,
                     std::vector< vector2 >& vt, std::vector< vector3 >& vn );

    Model* m_model = nullptr;            //!< Pointer to the associated Model.
    std::unique_ptr< Program > m_shader; //!< Shader program for this mesh.
    std::vector< Vertex > m_vertices;    //!< List of vertices for the mesh.
    std::string m_modelName;             //!< Name of the file for the model.
    GLsizei vertCount = 0;               //!< Number of vertices.
    GLuint vao = 0;                      //!< Vertex Array Object.
    GLuint vbo = 0;                      //!< Vertex Buffer Object.
};

} // namespace SquirrelEngine

#endif
