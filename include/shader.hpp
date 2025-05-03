
#ifndef SHADER_HPP
#define SHADER_HPP
#pragma once

#include <glad/glad.h>

#include "object.hpp"

namespace SquirrelEngine {

class ShaderBase : public Object {
public:
    ShaderBase();
    ShaderBase( GLuint t_handle );

    const std::string readFile( const std::string& filename );

    void getCompileStatus( const std::string& filename );

protected:
    GLuint m_handle;
};

class Shader : public ShaderBase {
public:
    Shader( const std::string& filename );
    ~Shader();

    GLenum getType() const;
    GLuint getHandle() const;

private:
    GLenum typeFromName( const std::string& filename );

protected:
    GLenum m_type;
};

class Program : public ShaderBase {
public:
    Program( const Shader& first, const Shader& second );
    Program( const std::string& firstFile, const std::string& secondFile );
    ~Program();

    GLuint getHandle() const;
};

} // namespace SquirrelEngine

#endif
