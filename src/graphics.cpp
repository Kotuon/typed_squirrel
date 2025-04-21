
#include "core.hpp"

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace SquirrelEngine {

Graphics::Graphics( Engine* t_engine, const int t_width, const int t_height )
    : System( t_engine, SystemType::ST_Graphics ), m_width( t_width ),
      m_height( t_height ) {}

Graphics::~Graphics() {}

StartupErrors Graphics::initialize() {
    if ( !glfwInit() ) {
        Trace::message( "Could not start GLFW." );
        return SE_GLFWFailedInit;
    }

    // Set core Window options (adjust version numbers if needed)
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    // Enable the GLFW runtime error callback function defined previously.
    glfwSetErrorCallback( Graphics::GLFWErrorCallback );

    // Set additional Window options
    glfwWindowHint( GLFW_RESIZABLE, false );
    glfwWindowHint( GLFW_SAMPLES, 4 ); // MSAA

    // Create Window using GLFW
    m_window = glfwCreateWindow( m_width, m_height, "", nullptr, nullptr );

    if ( !m_window ) {
        Trace::message( "Could not open GLFW Window." );

        glfwTerminate();
        return SE_GraphicsWindowFailedInit;
    }
    // Let the Window be the current OpenGL context and initialise glad
    glfwMakeContextCurrent( m_window );
    gladLoadGL();

    // Print device info
    printDeviceInfo();

    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );

    // Configure miscellaneous OpenGL settings
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glPointSize( 3.0 );

    // Set default colour after clearing the colour buffer
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glClearStencil( 0 );

    // Set callbacks
    glfwSetFramebufferSizeCallback( m_window,
                                    Graphics::frameBufferSizeCallback );
    glfwSetCursorEnterCallback( m_window, Graphics::cursorEnterCallback );

    glfwSetWindowUserPointer( m_window, this );
    glfwSetWindowCloseCallback( m_window, Graphics::closeWindowCallback );

    // Pre computing initial perspective projection matrix
    m_projection = glm::perspective< float >(
        glm::pi< float >() / 4.f,
        static_cast< float >( m_width ) / static_cast< float >( m_height ),
        0.1f, 100.f );

    return SE_Success;
}

void Graphics::render() {
    // TODO: Setup camera system

    // TODO: setup shaders system

    // Clear colour and depth buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
             GL_STENCIL_BUFFER_BIT );

    // TODO: Set render callbacks

    // Flip buffers
    glfwSwapBuffers( m_window );

    // Handle other events
    glfwPollEvents();
}

void Graphics::shutdown() { glfwTerminate(); }

void Graphics::GLFWErrorCallback( int Error, const char* Description ) {
    std::string message =
        "GLFW returned an error: " + std::string( Description ) +
        std::to_string( Error );

    Trace::message( message );
}

void Graphics::frameBufferSizeCallback( GLFWwindow*, int t_width,
                                        int t_height ) {
    glViewport( 0, 0, t_width, t_height );
}

void Graphics::cursorEnterCallback( GLFWwindow*, int t_entered ) {
    if ( t_entered ) {
        // The cursor entered the content area of the Window
        // glfwSetInputMode( Graphics::Instance().Window, GLFW_CURSOR,
        // GLFW_CURSOR_DISABLED ); cursorEntered = true;
    } else {
        // The cursor left the content area of the Window
    }
}

void Graphics::closeWindowCallback( GLFWwindow* t_window ) {
    glfwSetWindowShouldClose( t_window, GL_TRUE );
    Graphics* graphicsInstance =
        static_cast< Graphics* >( glfwGetWindowUserPointer( t_window ) );
    graphicsInstance->m_engine->triggerShutdown();
}

const char* Graphics::castToString( const unsigned char* t_input ) {
    return reinterpret_cast< const char* >( t_input );
}

void Graphics::printDeviceInfo() {
    Trace::message( fmt::format( "{}: {}",
                                 castToString( glGetString( GL_VENDOR ) ),
                                 castToString( glGetString( GL_RENDERER ) ) ) );
    Trace::message( fmt::format( "GLFW\t {}", glfwGetVersionString() ) );
    Trace::message( fmt::format( "OpenGL\t {}",
                                 castToString( glGetString( GL_VERSION ) ) ) );
    Trace::message( fmt::format(
        "GLSL\t {}",
        castToString( glGetString( GL_SHADING_LANGUAGE_VERSION ) ) ) );
}

SystemType Graphics::getType() { return SystemType::ST_Graphics; }

} // namespace SquirrelEngine
