/**
 *
 * @file keyboard.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Keyboard class, which represents a keyboard input device
 * for SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#pragma once

#include <array>

#include "inputDevice.hpp"
#include "keyList.hpp"

namespace SquirrelEngine {
class Engine;

/**
 * @brief Represents a keyboard input device.
 */
class Keyboard : public InputDevice {
public:
    /**
     * @brief Default constructor for Keyboard.
     */
    Keyboard();

    /**
     * @brief Virtual destructor for Keyboard.
     */
    ~Keyboard() = default;

    /**
     * @brief Initializes the keyboard device.
     */
    void initialize();

    /**
     * @brief Gets the state of a keyboard button.
     * @param button The button index.
     * @return The state of the button as a float.
     */
    const float getButtonState( const int button );

    /**
     * @brief Sets the state of a keyboard button.
     * @param button The button index.
     * @param state The new state of the button.
     */
    void setButtonState( const int button, const float state );

    /**
     * @brief Gets the type of the input device.
     * @return The device type as an int.
     */
    const int getType() override { return InputDeviceType::UD_Keyboard; }

protected:
    std::array< int, KEY_LAST > m_keyStates = { 0 }; //!< Array of key states.
};

} // namespace SquirrelEngine

#endif
