/**
 *
 * @file inputAction.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the InputAction class, which represents input events and
 * actions in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "inputAction.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for InputAction.
 */
InputAction::InputAction() : amount( 0.f ), device( nullptr ) {}

/**
 * @brief Constructs an InputAction with type, device, and amount.
 * @param t_type The type of input action.
 * @param t_device Pointer to the input device.
 * @param t_amount The amount or value of the input.
 */
InputAction::InputAction( const std::string t_type, InputDevice* t_device,
                          const float t_amount )
    : type( t_type ), device( t_device ), amount( t_amount ) {}

} // namespace SquirrelEngine
