
#include <fstream>

#include "core.hpp"

#include "shader.hpp"

namespace SquirrelEngine {

//---------- Shader Base ----------//
ShaderBase::ShaderBase() {}

ShaderBase::ShaderBase( GLuint t_handle ) : m_handle( t_handle ) {}

const std::string ShaderBase::readFile( const std::string& FileName ) {
    std::string content;

    std::ifstream file( FileName );
    if ( !file.is_open() ) {
        Trace::message( fmt::format( "Failed to open shader {}.", FileName ) );
        return nullptr;
    }

    std::string line = "";
    while ( !file.eof() ) {
        getline( file, line );
        content.append( line + "\n" );
    }

    file.close();
    content.append( "\0" );
    return content;
}

void ShaderBase::getCompileStatus( const std::string& filename ) {
    GLint success = 0;
    GLint logSize = 0;

    glGetShaderiv( m_handle, GL_COMPILE_STATUS, &success );
    if ( success == GL_FALSE ) {
        glGetShaderiv( m_handle, GL_INFO_LOG_LENGTH, &logSize );
        GLchar* infoLog = new GLchar[logSize];
        glGetShaderInfoLog( m_handle, logSize, &logSize, infoLog );
        glDeleteShader( m_handle );
        Trace::message(
            fmt::format( "Vertex Shader {}: {}\n", filename, infoLog ) );
        delete[] infoLog;
    }
}

//---------- Shader ----------//
Shader::Shader( const std::string& filename )
    : m_type( typeFromName( filename ) ) {
    m_handle = glCreateShader( m_type );

    std::string sourceStr = readFile( filename );
    const char* source = sourceStr.c_str();
    if ( !source ) {
        Trace::message( fmt::format( "Bad source file: {}", filename ) );
        return;
    }

    glShaderSource( m_handle, 1, &source, nullptr );
    glCompileShader( m_handle );

    getCompileStatus( filename );
}

Shader::~Shader() { glDeleteShader( m_handle ); }

GLenum Shader::getType() const { return m_type; }

GLuint Shader::getHandle() const { return m_handle; }

GLenum Shader::typeFromName( const std::string& filename ) {
    if ( filename.ends_with( ".vert" ) ) {
        return GL_VERTEX_SHADER;
    } else if ( filename.ends_with( ".frag" ) ) {
        return GL_FRAGMENT_SHADER;
    } else if ( filename.ends_with( ".geom" ) ) {
        return GL_GEOMETRY_SHADER;
    } else if ( filename.ends_with( ".tesc" ) ) {
        return GL_TESS_CONTROL_SHADER;
    } else if ( filename.ends_with( ".tese" ) ) {
        return GL_TESS_EVALUATION_SHADER;
    } else if ( filename.ends_with( ".comp" ) ) {
        return GL_COMPUTE_SHADER;
    }

    return 0;
}

//---------- Program ----------//
Program::Program( const Shader& first, const Shader& second )
    : ShaderBase( glCreateProgram() ) {
    glAttachShader( m_handle, first.getHandle() );
    glAttachShader( m_handle, second.getHandle() );

    glLinkProgram( m_handle );
}

Program::Program( const std::string& firstFile, const std::string& secondFile )
    : ShaderBase( glCreateProgram() ) {
    Shader first( firstFile );
    Shader second( secondFile );

    glAttachShader( m_handle, first.getHandle() );
    glAttachShader( m_handle, second.getHandle() );

    glLinkProgram( m_handle );
}

Program::~Program() { glDeleteProgram( m_handle ); }

GLuint Program::getHandle() const { return m_handle; }

} // namespace SquirrelEngine
