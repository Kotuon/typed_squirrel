/**
 *
 * @file mouse.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Mouse class, which represents a mouse input device for
 * SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <GLFW/glfw3.h>

#include "engine.hpp"
#include "inputSystem.hpp"
#include "mouse.hpp"
#include "window.hpp"

namespace SquirrelEngine {

/**
 * @brief GLFW mouse button callback for mouse input.
 * @param window Pointer to the GLFW window.
 * @param button Mouse button code.
 * @param action Mouse button action (press/release).
 * @param mods Modifier keys.
 */
static void mouseCallback( GLFWwindow*, int button, int action, int ) {
    InputSystem* inputSystem = getSystem< InputSystem >();

    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    const int state = ( action == GLFW_PRESS ) ? 1 : 0;
    mouse->setButtonState( button, static_cast< float >( state ) );

    inputSystem->triggerAction( mouse, button, static_cast< float >( state ) );
}

/**
 * @brief GLFW mouse scroll callback for mouse input.
 * @param window Pointer to the GLFW window.
 * @param xoffset Scroll offset in X direction (unused).
 * @param yoffset Scroll offset in Y direction.
 */
static void mouseScrollCallback( GLFWwindow*, double, double yoffset ) {
    InputSystem* inputSystem = getSystem< InputSystem >();

    Mouse* mouse = inputSystem->findInputDevice< Mouse >();

    float scroll = mouse->getButtonState( MouseButtons::BUTTON_SCROLL );
    scroll += static_cast< float >( yoffset );
    mouse->setButtonState( MouseButtons::BUTTON_SCROLL, scroll );

    inputSystem->triggerAction( mouse, MouseButtons::BUTTON_SCROLL,
                                static_cast< float >( yoffset ) );
}

/**
 * @brief Default constructor for Mouse.
 */
Mouse::Mouse()
    : m_lastCursorPosition( 0.f ), m_cursorMode( GLFW_CURSOR_NORMAL ) {}

/**
 * @brief Initializes the mouse device and sets up callbacks.
 */
void Mouse::initialize() {
    Window* window = Engine::instance()->getWindowHandle();

    glfwSetMouseButtonCallback( window->getHandle(), mouseCallback );
    glfwSetScrollCallback( window->getHandle(), mouseScrollCallback );
}

/**
 * @brief Gets the state of a mouse button.
 * @param button The button index.
 * @return The state of the button as a float.
 */
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

/**
 * @brief Sets the state of a mouse button.
 * @param button The button index.
 * @param state The new state of the button.
 */
void Mouse::setButtonState( const int button, const float state ) {
    if ( button < 0 || BUTTON_MOUSE_LAST < button ) {
        Trace::message( "Button outside of range." );
        return;
    }

    m_buttonStates[button] = static_cast< int >( state );
}

/**
 * @brief Gets the current cursor position.
 * @return The cursor position as a vector2.
 */
const vector2 Mouse::getCursorPosition() {
    Window* window = Engine::instance()->getWindowHandle();

    double xpos, ypos;
    glfwGetCursorPos( window->getHandle(), &xpos, &ypos );

    return vector2( xpos, ypos );
}

/**
 * @brief Gets the delta of the cursor position since the last update.
 * @return The cursor delta as a vector2.
 */
const vector2 Mouse::getCursorDelta() {
    vector2 currPosition = getCursorPosition();
    vector2 lastPosition = m_lastCursorPosition;

    m_lastCursorPosition = currPosition;

    return currPosition - lastPosition;
}

/**
 * @brief Sets the cursor mode (e.g., normal, hidden, disabled).
 * @param t_cursorMode The cursor mode to set.
 */
void Mouse::setCursorMode( const int t_cursorMode ) {
    if ( t_cursorMode == m_cursorMode ) {
        return;
    }

    GLFWwindow* window = Engine::instance()->getWindowHandle()->getHandle();

    glfwSetInputMode( window, GLFW_CURSOR, t_cursorMode );
    m_cursorMode = t_cursorMode;

    m_lastCursorPosition = getCursorPosition();
}

} // namespace SquirrelEngine
