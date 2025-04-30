
#include <GLFW/glfw3.h>

#include "engine.hpp"
#include "inputSystem.hpp"
#include "mouse.hpp"
#include "window.hpp"

namespace SquirrelEngine {

static void mouseCallback( GLFWwindow*, int button, int action, int ) {
    InputSystem* inputSystem = getSystem< InputSystem >();

    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    const int state = ( action == GLFW_PRESS ) ? 1 : 0;
    mouse->setButtonState( button, static_cast< float >( state ) );

    inputSystem->triggerAction( mouse, button, static_cast< float >( state ) );
}

static void mouseScrollCallback( GLFWwindow*, double, double yoffset ) {
    InputSystem* inputSystem = getSystem< InputSystem >();

    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    float scroll = mouse->getButtonState( MouseButtons::BUTTON_SCROLL );
    scroll += static_cast< float >( yoffset );
    mouse->setButtonState( MouseButtons::BUTTON_SCROLL, scroll );

    inputSystem->triggerAction( mouse, MouseButtons::BUTTON_SCROLL,
                                static_cast< float >( yoffset ) );
}

Mouse::Mouse() : m_lastCursorPosition( 0.f ) {}

void Mouse::initialize() {
    Window* window = Engine::instance()->getWindowHandle();

    glfwSetMouseButtonCallback( window->getHandle(), mouseCallback );
    glfwSetScrollCallback( window->getHandle(), mouseScrollCallback );
}

const float Mouse::getButtonState( const int button ) {
    if ( button < 0 || BUTTON_MOUSE_LAST < button ) {
        Trace::message( "Button outside of range." );
        return 0.f;
    }

    if ( button == MouseButtons::BUTTON_SCROLL ) {
        const float amount = static_cast< float >( m_buttonStates[button] );
        m_buttonStates[button] = 0;
        return amount;
    }

    return static_cast< float >( m_buttonStates[button] );
}

void Mouse::setButtonState( const int button, const float state ) {
    if ( button < 0 || BUTTON_MOUSE_LAST < button ) {
        Trace::message( "Button outside of range." );
        return;
    }

    m_buttonStates[button] = static_cast< int >( state );
}

const vector2 Mouse::getCursorPosition() {
    Window* window = Engine::instance()->getWindowHandle();

    double xpos, ypos;
    glfwGetCursorPos( window->getHandle(), &xpos, &ypos );

    return vector2( xpos, ypos );
}

const vector2 Mouse::getCursorDelta() {
    vector2 currPosition = getCursorPosition();
    vector2 lastPosition = m_lastCursorPosition;

    m_lastCursorPosition = currPosition;

    return currPosition - lastPosition;
}

} // namespace SquirrelEngine
