
#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once

#include "object.hpp"

struct GLFWwindow;

namespace SquirrelEngine {
enum StartupErrors : unsigned;

class Window : public Object {
public:
    Window();
    ~Window() = default;

    StartupErrors create( const std::string title, const int width,
                          const int height, bool isFullscreen );

    void pollEvents();
    void swapBuffer();

    bool isClosing();

    void size( int& width, int& height );
    void frameBufferSize( int& width, int& height );

    GLFWwindow* getHandle();

    static void closeWindowCallback( GLFWwindow* t_window );

protected:
    GLFWwindow* m_window;
};

}; // namespace SquirrelEngine

#endif
