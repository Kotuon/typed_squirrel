/**
 *
 * @file window.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Window class, which manages the application window and
 * its properties in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"
#include "utils/trace.hpp"
#include "error_codes.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for Window.
 */
Window::Window() : m_window( nullptr ) {}

/**
 * @brief Creates the window with the specified parameters.
 * @param title The window title.
 * @param width The window width.
 * @param height The window height.
 * @param isFullscreen Whether the window should be fullscreen.
 * @return StartupErrors indicating success or failure.
 */
StartupErrors Window::create( const std::string title, const int width,
                              const int height, bool isFullscreen ) {
    if ( !glfwInit() ) {
        Trace::message( "Could not start GLFW." );
        return StartupErrors::SE_GLFWFailedInit;
    }

    // Specify the minimum OpenGL version
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );

    glfwWindowHint( GLFW_SAMPLES, 4 );

    if ( isFullscreen ) {
        // Get our primary monitor
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode( primaryMonitor );
        const unsigned int fullscreenWidth = mode->width;
        const unsigned int fullscreenHeight = mode->height;

        m_window = glfwCreateWindow( fullscreenWidth, fullscreenHeight,
                                     title.c_str(), primaryMonitor, nullptr );
    } else {
        m_window =
            glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr );
    }

    // Ensure the Window is set up correctly
    if ( !m_window ) {
        Trace::message( "Could not open GLFW Window." );

        glfwTerminate();
        return StartupErrors::SE_GraphicsWindowFailedInit;
    }

    // Let the Window be the current OpenGL context and initialise glad
    glfwMakeContextCurrent( m_window );
    gladLoadGL();

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
    glClearColor( 0.6f, 0.6f, 0.6f, 1.0f );
    glClearStencil( 0 );

    glfwSetWindowCloseCallback( m_window, Window::closeWindowCallback );

    return StartupErrors::SE_Success;
}

/**
 * @brief Polls window events (input, close, etc.).
 */
void Window::pollEvents() { glfwPollEvents(); }

/**
 * @brief Swaps the window's front and back buffers.
 */
void Window::swapBuffer() { glfwSwapBuffers( m_window ); }

/**
 * @brief Checks if the window is closing.
 * @return True if the window is closing, false otherwise.
 */
bool Window::isClosing() { return ( glfwWindowShouldClose( m_window ) ); }

/**
 * @brief Gets the current window size.
 * @param width Reference to store the width.
 * @param height Reference to store the height.
 */
void Window::size( int& width, int& height ) {
    glfwGetWindowSize( m_window, &width, &height );
}

/**
 * @brief Gets the current framebuffer size.
 * @param width Reference to store the framebuffer width.
 * @param height Reference to store the framebuffer height.
 */
void Window::frameBufferSize( int& width, int& height ) {
    glfwGetFramebufferSize( m_window, &width, &height );
}

/**
 * @brief Gets the underlying GLFW window handle.
 * @return Pointer to the GLFWwindow.
 */
GLFWwindow* Window::getHandle() { return m_window; }

/**
 * @brief GLFW callback for window close event.
 * @param t_window Pointer to the GLFWwindow.
 */
void Window::closeWindowCallback( GLFWwindow* t_window ) {
    glfwSetWindowShouldClose( t_window, GL_TRUE );
}

} // namespace SquirrelEngine
