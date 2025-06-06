/**
 *
 * @file mesh.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
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

class Mesh : public Object {
public:
    Mesh();
    Mesh( const Mesh& other );
    Mesh( const Mesh* other );
    Mesh( Model* t_model );

    ~Mesh();

    bool load( std::string t_modelName );

    void draw();

    void setShader( Program* t_shader );
    const Program* getShader() const;

    void loadShader( const std::string& vertName, const std::string& fragName );

    std::string getModelName() const;

private:
    bool read( std::string t_modelName );
    void insertData( char* data[3], std::vector< vector3 >& v,
                     std::vector< vector2 >& vt, std::vector< vector3 >& vn );

    Model* m_model;
    std::unique_ptr< Program > m_shader;

    std::vector< float > m_vertices; //!< Contains vertices of model
    std::vector< float > m_normals;  //!< Contains normals of model
    std::vector< float > m_uvs;      //!< Contains uv data of model
    std::string m_modelName;         //!< Name of the file for the model
    GLuint m_vertexbuffer;           //!< Vertex buffer of model
    GLuint m_normalbuffer;           //!< Normal buffer of model
    GLuint m_uvbuffer;               //!< UV buffer of model
};

} // namespace SquirrelEngine

#endif
