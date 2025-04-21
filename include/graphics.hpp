
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#pragma once

#include <glm/glm.hpp>
#include "system.hpp"

class GLFWwindow;

namespace SquirrelEngine {
class Engine;

class Graphics : public System {
public:
    /**
     * @brief Construct a new Graphics object
     *
     * @param t_engine Reference to engine
     * @param t_width Width of window
     * @param t_height Height of window
     */
    Graphics( Engine* t_engine, const int t_width = 800,
              const int t_height = 600 );
    virtual ~Graphics();

    void render();
    virtual void shutdown();

    /**
     * @brief Initializes graphics window and settings
     *
     * @return true
     * @return false
     */
    StartupErrors initialize();

    static SystemType getType();

private:
    /**
     * @brief Prints out GLFW error
     *
     * @param Error
     * @param Description
     */
    static void GLFWErrorCallback( int Error, const char* Description );

    static void frameBufferSizeCallback( GLFWwindow* t_window, int t_width,
                                         int t_height );
    static void cursorEnterCallback( GLFWwindow* t_window, int t_entered );
    static void closeWindowCallback( GLFWwindow* t_window );

    static const char* castToString( const unsigned char* t_input );
    static void printDeviceInfo();

    GLFWwindow* m_window; //!< Application window pointer

    glm::mat4 m_projection;

    int m_width;  //!< Window width
    int m_height; //!< Window height
};

} // namespace SquirrelEngine

#endif
