/**
 *
 * @file inputAction.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the InputAction class, which represents input events and
 * actions in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef INPUTACTION_HPP
#define INPUTACTION_HPP
#pragma once

#include "event.hpp"
#include "inputDevice.hpp"

namespace SquirrelEngine {

class InputAction : public Event {
public:
    /**
     * @brief Default constructor for InputAction.
     */
    InputAction();

    /**
     * @brief Constructs an InputAction with type, device, and amount.
     * @param t_type The type of input action.
     * @param t_device Pointer to the input device.
     * @param t_amount The amount or value of the input.
     */
    InputAction( const std::string t_type, InputDevice* t_device,
                 const float t_amount );

    /**
     * @brief Virtual destructor for InputAction.
     */
    ~InputAction() = default;

    std::string type;    //!< The type of input action.
    InputDevice* device; //!< Pointer to the input device.
    float amount;        //!< The amount or value of the input.
};

} // namespace SquirrelEngine

#endif
