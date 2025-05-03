
#ifndef MOUSE_HPP
#define MOUSE_HPP
#pragma once

#include <array>

#include "inputDevice.hpp"
#include "math_types.hpp"

namespace SquirrelEngine {
enum MouseButtons {
    BUTTON_LEFT = 1,
    BUTTON_RIGHT,
    BUTTON_MIDDLE,
    BUTTON_SCROLL,
    BUTTON_MOUSE_LAST
};

class Mouse : public InputDevice {
public:
    Mouse();
    ~Mouse() = default;

    void initialize();

    const float getButtonState( const int button );

    void setButtonState( const int button, const float state );

    const int getType() { return InputDeviceType::UD_Mouse; }

    const vector2 getCursorPosition();

    const vector2 getCursorDelta();

    void setCursorMode( const int t_cursorMode );

protected:
    std::array< int, BUTTON_MOUSE_LAST > m_buttonStates = { 0 };
    vector2 m_lastCursorPosition;

    int m_cursorMode;
};

} // namespace SquirrelEngine

#endif
