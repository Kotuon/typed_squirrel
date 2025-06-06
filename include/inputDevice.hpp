/**
 *
 * @file inputDevice.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the InputDevice class, which represents input devices for
 * SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef INPUTDEVICE_HPP
#define INPUTDEVICE_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {
class Engine;

/**
 * @brief Base class for input devices in SquirrelEngine.
 */
class InputDevice : public Object {
public:
    /**
     * @brief Default constructor for InputDevice.
     */
    InputDevice() = default;

    /**
     * @brief Virtual destructor for InputDevice.
     */
    virtual ~InputDevice() = default;

    /**
     * @brief Initializes the input device.
     */
    virtual void initialize() {}

    /**
     * @brief Updates the input device state.
     */
    virtual void update() {}

    /**
     * @brief Gets the state of a button.
     * @param button The button index.
     * @return The state of the button as a float.
     */
    virtual const float getButtonState( const int button ) = 0;

    /**
     * @brief Sets the state of a button.
     * @param button The button index.
     * @param state The new state of the button.
     */
    virtual void setButtonState( const int button, const float state ) = 0;

    /**
     * @brief Gets the type of the input device.
     * @return The device type as an int.
     */
    virtual const int getType() = 0;

protected:
    /**
     * @brief Enum for input device types.
     */
    enum InputDeviceType : unsigned {
        UD_Keyboard = 1, //!< Keyboard device type.
        UD_Mouse = 2,    //!< Mouse device type.
        UD_Gamepad = 3   //!< Gamepad device type.
    };
};

} // namespace SquirrelEngine

#endif
