
#ifndef INPUTDEVICE_HPP
#define INPUTDEVICE_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {
class Engine;

class InputDevice : public Object {
public:
    InputDevice() = default;
    virtual ~InputDevice() = default;

    virtual void initialize() {}
    virtual void update() {}

    virtual const float getButtonState( const int button ) = 0;

    virtual void setButtonState( const int button, const float state ) = 0;

    virtual const int getType() = 0;

protected:
    enum InputDeviceType : unsigned {
        UD_Keyboard = 1,
        UD_Mouse = 2,
        UD_Gamepad = 3
    };
};

} // namespace SquirrelEngine

#endif
