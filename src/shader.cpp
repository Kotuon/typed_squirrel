/**
 *
 * @file shader.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Shader, ShaderBase, and Program classes, which handle
 * OpenGL shader compilation and linking for SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <fstream>

#include "core.hpp"
#include "shader.hpp"

namespace SquirrelEngine {

//---------- Shader Base ----------//

/**
 * @brief Default constructor for ShaderBase.
 */
ShaderBase::ShaderBase() {}

/**
 * @brief Constructs a ShaderBase with a given OpenGL handle.
 * @param t_handle OpenGL shader or program handle.
 */
ShaderBase::ShaderBase( GLuint t_handle ) : m_handle( t_handle ) {}

/**
 * @brief Reads the contents of a shader file.
 * @param FileName Path to the shader file.
 * @return Contents of the file as a string.
 */
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

/**
 * @brief Checks and prints the compile status of a shader.
 * @param filename Name of the shader file.
 */
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

/**
 * @brief Gets the location of a uniform or attribute in the shader program.
 * @param locationName Name of the uniform or attribute.
 * @return Location as GLuint.
 */
GLuint ShaderBase::getLocation( const char* locationName ) const {
    return glGetUniformLocation( m_handle, locationName );
}

void ShaderBase::setFloat( const char* locationName, const float value ) const {
    glUniform1f( getLocation( locationName ), value );
}

void ShaderBase::setInt( const char* locationName, const int value ) const {
    glUniform1i( getLocation( locationName ), value );
}

//---------- Shader ----------//

/**
 * @brief Constructs a Shader from a file.
 * @param filename Path to the shader file.
 */
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

/**
 * @brief Destructor for Shader.
 */
Shader::~Shader() { glDeleteShader( m_handle ); }

/**
 * @brief Gets the type of the shader (e.g., GL_VERTEX_SHADER).
 * @return Shader type as GLenum.
 */
GLenum Shader::getType() const { return m_type; }

/**
 * @brief Gets the OpenGL handle for the shader.
 * @return Shader handle as GLuint.
 */
GLuint Shader::getHandle() const { return m_handle; }

/**
 * @brief Determines the shader type from the filename extension.
 * @param filename Path to the shader file.
 * @return Shader type as GLenum.
 */
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

/**
 * @brief Copy constructor for Program.
 * @param other Program to copy from.
 */
Program::Program( const Program& other ) : ShaderBase( other.m_handle ) {}

/**
 * @brief Copy constructor from pointer for Program.
 * @param other Pointer to Program to copy from.
 */
Program::Program( const Program* other ) : ShaderBase( other->m_handle ) {}

/**
 * @brief Constructs a Program from two shaders.
 * @param first First shader.
 * @param second Second shader.
 */
Program::Program( const Shader& vertex, const Shader& fragment )
    : ShaderBase( glCreateProgram() ) {
    glAttachShader( m_handle, vertex.getHandle() );
    glAttachShader( m_handle, fragment.getHandle() );

    glLinkProgram( m_handle );
}

Program::Program( const Shader& vertex, const Shader& geometry,
                  const Shader& fragment )
    : ShaderBase( glCreateProgram() ) {
    glAttachShader( m_handle, vertex.getHandle() );
    glAttachShader( m_handle, geometry.getHandle() );
    glAttachShader( m_handle, fragment.getHandle() );

    glLinkProgram( m_handle );
}

/**
 * @brief Constructs a Program from two shader files.
 * @param firstFile Vertex shader file.
 * @param secondFile Fragment shader file.
 */
Program::Program( const std::string& vertexFile,
                  const std::string& fragmentFile )
    : ShaderBase( glCreateProgram() ) {
    Shader first( vertexFile );
    Shader second( fragmentFile );

    glAttachShader( m_handle, first.getHandle() );
    glAttachShader( m_handle, second.getHandle() );

    glLinkProgram( m_handle );
}

Program::Program( const std::string& vertexFile,
                  const std::string& geometryFile,
                  const std::string& fragmentFile )
    : ShaderBase( glCreateProgram() ) {
    Shader vertex( vertexFile );
    Shader geometry( geometryFile );
    Shader fragment( fragmentFile );

    glAttachShader( m_handle, vertex.getHandle() );
    glAttachShader( m_handle, geometry.getHandle() );
    glAttachShader( m_handle, fragment.getHandle() );

    glLinkProgram( m_handle );
}

Program::Program( const Shader& computeShader )
    : ShaderBase( glCreateProgram() ) {
    glAttachShader( m_handle, computeShader.getHandle() );

    glLinkProgram( m_handle );
}

Program::Program( const std::string& computeFile )
    : ShaderBase( glCreateProgram() ) {
    Shader computeShader( computeFile );

    glAttachShader( m_handle, computeShader.getHandle() );

    glLinkProgram( m_handle );
}

/**
 * @brief Destructor for Program.
 */
Program::~Program() { glDeleteProgram( m_handle ); }

void Program::use() const { glUseProgram( m_handle ); }

/**
 * @brief Gets the OpenGL handle for the program.
 * @return Program handle as GLuint.
 */
GLuint Program::getHandle() const { return m_handle; }

} // namespace SquirrelEngine
