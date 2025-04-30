
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#pragma once

#include <array>

#include "inputDevice.hpp"
#include "keyList.hpp"

namespace SquirrelEngine {
class Engine;

class Keyboard : public InputDevice {
public:
    Keyboard();
    ~Keyboard() = default;

    void initialize();

    const float getButtonState( const int button );

    void setButtonState( const int button, const float state );

    const int getType() { return InputDeviceType::UD_Keyboard; }

protected:
    std::array< int, KEY_LAST > m_keyStates = { 0 };
};

} // namespace SquirrelEngine

#endif
