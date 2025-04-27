
#ifndef INPUTACTION_HPP
#define INPUTACTION_HPP
#pragma once

#include "event.hpp"
#include "inputDevice.hpp"

namespace SquirrelEngine {

class InputAction : public Event {
public:
    InputAction();
    InputAction( const std::string t_type, InputDevice* t_device,
                 const float t_amount );
    ~InputAction() = default;

    std::string type;
    InputDevice* device;
    float amount;
};

} // namespace SquirrelEngine

#endif
