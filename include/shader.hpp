/**
 *
 * @file shader.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Shader, ShaderBase, and Program classes, which handle
 * OpenGL shader compilation and linking for SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef SHADER_HPP
#define SHADER_HPP
#pragma once

#include <glad/glad.h>

#include "object.hpp"

namespace SquirrelEngine {

/**
 * @brief Base class for shader objects.
 */
class ShaderBase : public Object {
public:
    /**
     * @brief Default constructor for ShaderBase.
     */
    ShaderBase();

    /**
     * @brief Constructs a ShaderBase with a given OpenGL handle.
     * @param t_handle OpenGL shader or program handle.
     */
    ShaderBase( GLuint t_handle );

    /**
     * @brief Reads the contents of a shader file.
     * @param filename Path to the shader file.
     * @return Contents of the file as a string.
     */
    const std::string readFile( const std::string& filename );

    /**
     * @brief Checks and prints the compile status of a shader.
     * @param filename Name of the shader file.
     */
    void getCompileStatus( const std::string& filename );

    /**
     * @brief Gets the location of a uniform or attribute in the shader program.
     * @param locationName Name of the uniform or attribute.
     * @return Location as GLuint.
     */
    GLuint getLocation( const char* locationName ) const;

    void setFloat( const char* locationName, const float value ) const;

    void setInt( const char* locationName, const int value ) const;

protected:
    GLuint m_handle; //!< OpenGL handle for the shader or program.
};

/**
 * @brief Represents an OpenGL shader (vertex, fragment, etc.).
 */
class Shader : public ShaderBase {
public:
    /**
     * @brief Constructs a Shader from a file.
     * @param filename Path to the shader file.
     */
    Shader( const std::string& filename );

    /**
     * @brief Destructor for Shader.
     */
    ~Shader();

    /**
     * @brief Gets the type of the shader (e.g., GL_VERTEX_SHADER).
     * @return Shader type as GLenum.
     */
    GLenum getType() const;

    /**
     * @brief Gets the OpenGL handle for the shader.
     * @return Shader handle as GLuint.
     */
    GLuint getHandle() const;

private:
    /**
     * @brief Determines the shader type from the filename extension.
     * @param filename Path to the shader file.
     * @return Shader type as GLenum.
     */
    GLenum typeFromName( const std::string& filename );

protected:
    GLenum m_type; //!< OpenGL shader type (e.g., GL_VERTEX_SHADER).
};

/**
 * @brief Represents an OpenGL shader program (linked shaders).
 */
class Program : public ShaderBase {
public:
    /**
     * @brief Copy constructor for Program.
     * @param other Program to copy from.
     */
    Program( const Program& other );

    /**
     * @brief Copy constructor from pointer for Program.
     * @param other Pointer to Program to copy from.
     */
    Program( const Program* other );

    /**
     * @brief Constructs a Program from two shaders.
     * @param first First shader.
     * @param second Second shader.
     */
    Program( const Shader& vertex, const Shader& fragment );

    Program( const Shader& vertex, const Shader& geometry,
             const Shader& fragment );

    /**
     * @brief Constructs a Program from two shader files.
     * @param firstFile Vertex shader file.
     * @param secondFile Fragment shader file.
     */
    Program( const std::string& vertexFile, const std::string& fragmentFile );

    Program( const std::string& vertexFile, const std::string& geometryFile,
             const std::string& fragmentFile );

    Program( const Shader& computeShader );

    Program( const std::string& computeFile );

    /**
     * @brief Destructor for Program.
     */
    ~Program();

    void use() const;

    /**
     * @brief Gets the OpenGL handle for the program.
     * @return Program handle as GLuint.
     */
    GLuint getHandle() const;
};

} // namespace SquirrelEngine

#endif
