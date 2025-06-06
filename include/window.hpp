/**
 *
 * @file window.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Window class, which manages the application window and
 * its properties in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once

#include "object.hpp"

struct GLFWwindow;

namespace SquirrelEngine {
enum StartupErrors : unsigned;

/**
 * @brief Manages the application window and its properties.
 */
class Window : public Object {
public:
    /**
     * @brief Default constructor for Window.
     */
    Window();

    /**
     * @brief Virtual destructor for Window.
     */
    ~Window() = default;

    /**
     * @brief Creates the window with the specified parameters.
     * @param title The window title.
     * @param width The window width.
     * @param height The window height.
     * @param isFullscreen Whether the window should be fullscreen.
     * @return StartupErrors indicating success or failure.
     */
    StartupErrors create( const std::string title, const int width,
                          const int height, bool isFullscreen );

    /**
     * @brief Polls window events (input, close, etc.).
     */
    void pollEvents();

    /**
     * @brief Swaps the window's front and back buffers.
     */
    void swapBuffer();

    /**
     * @brief Checks if the window is closing.
     * @return True if the window is closing, false otherwise.
     */
    bool isClosing();

    /**
     * @brief Gets the current window size.
     * @param width Reference to store the width.
     * @param height Reference to store the height.
     */
    void size( int& width, int& height );

    /**
     * @brief Gets the current framebuffer size.
     * @param width Reference to store the framebuffer width.
     * @param height Reference to store the framebuffer height.
     */
    void frameBufferSize( int& width, int& height );

    /**
     * @brief Gets the underlying GLFW window handle.
     * @return Pointer to the GLFWwindow.
     */
    GLFWwindow* getHandle();

    /**
     * @brief GLFW callback for window close event.
     * @param t_window Pointer to the GLFWwindow.
     */
    static void closeWindowCallback( GLFWwindow* t_window );

protected:
    GLFWwindow* m_window; //!< Pointer to the GLFW window.
};

}; // namespace SquirrelEngine

#endif
