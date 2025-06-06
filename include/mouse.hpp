/**
 *
 * @file mouse.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Mouse class, which represents a mouse input device for
 * SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef MOUSE_HPP
#define MOUSE_HPP
#pragma once

#include <array>

#include "inputDevice.hpp"
#include "math_types.hpp"

namespace SquirrelEngine {

/**
 * @brief Enum representing mouse buttons.
 */
enum MouseButtons {
    BUTTON_LEFT = 1,  //!< Left mouse button
    BUTTON_RIGHT,     //!< Right mouse button
    BUTTON_MIDDLE,    //!< Middle mouse button
    BUTTON_SCROLL,    //!< Scroll wheel
    BUTTON_MOUSE_LAST //!< Last mouse button (sentinel)
};

/**
 * @brief Represents a mouse input device.
 */
class Mouse : public InputDevice {
public:
    /**
     * @brief Default constructor for Mouse.
     */
    Mouse();

    /**
     * @brief Virtual destructor for Mouse.
     */
    ~Mouse() = default;

    /**
     * @brief Initializes the mouse device.
     */
    void initialize();

    /**
     * @brief Gets the state of a mouse button.
     * @param button The button index.
     * @return The state of the button as a float.
     */
    const float getButtonState( const int button );

    /**
     * @brief Sets the state of a mouse button.
     * @param button The button index.
     * @param state The new state of the button.
     */
    void setButtonState( const int button, const float state );

    /**
     * @brief Gets the type of the input device.
     * @return The device type as an int.
     */
    const int getType() override { return InputDeviceType::UD_Mouse; }

    /**
     * @brief Gets the current cursor position.
     * @return The cursor position as a vector2.
     */
    const vector2 getCursorPosition();

    /**
     * @brief Gets the delta of the cursor position since the last update.
     * @return The cursor delta as a vector2.
     */
    const vector2 getCursorDelta();

    /**
     * @brief Sets the cursor mode (e.g., normal, hidden, disabled).
     * @param t_cursorMode The cursor mode to set.
     */
    void setCursorMode( const int t_cursorMode );

protected:
    std::array< int, BUTTON_MOUSE_LAST > m_buttonStates = {
        0 };                      //!< Array of mouse button states.
    vector2 m_lastCursorPosition; //!< Last recorded cursor position.
    int m_cursorMode;             //!< Current cursor mode.
};

} // namespace SquirrelEngine

#endif
