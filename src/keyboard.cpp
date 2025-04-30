
#include <GLFW/glfw3.h>

#include "engine.hpp"
#include "inputSystem.hpp"
#include "keyboard.hpp"
#include "window.hpp"

namespace SquirrelEngine {
std::array< int, GLFW_KEY_LAST > keyMappings;

static void keyboardCallback( GLFWwindow*, int key, int, int action, int ) {
    InputSystem* inputSystem = getSystem< InputSystem >();

    Keyboard* keyboard =
        dynamic_cast< Keyboard* >( inputSystem->findInputDevice< Keyboard >() );

    const int state = ( action == GLFW_PRESS || action == GLFW_REPEAT ) ? 1 : 0;
    keyboard->setButtonState( keyMappings[key], static_cast< float >( state ) );

    inputSystem->triggerAction( keyboard, keyMappings[key],
                                static_cast< float >( state ) );
}

Keyboard::Keyboard() {}

void Keyboard::initialize() {
    Window* window = Engine::instance()->getWindowHandle();
    glfwSetKeyCallback( window->getHandle(), keyboardCallback );

    // Map keys from GLFW to internal mappings
    keyMappings[GLFW_KEY_0] = KEY_0;
    keyMappings[GLFW_KEY_1] = KEY_1;
    keyMappings[GLFW_KEY_2] = KEY_2;
    keyMappings[GLFW_KEY_3] = KEY_3;
    keyMappings[GLFW_KEY_4] = KEY_4;
    keyMappings[GLFW_KEY_5] = KEY_5;
    keyMappings[GLFW_KEY_6] = KEY_6;
    keyMappings[GLFW_KEY_7] = KEY_7;
    keyMappings[GLFW_KEY_8] = KEY_8;
    keyMappings[GLFW_KEY_9] = KEY_9;
    keyMappings[GLFW_KEY_A] = KEY_A;
    keyMappings[GLFW_KEY_B] = KEY_B;
    keyMappings[GLFW_KEY_C] = KEY_C;
    keyMappings[GLFW_KEY_D] = KEY_D;
    keyMappings[GLFW_KEY_E] = KEY_E;
    keyMappings[GLFW_KEY_F] = KEY_F;
    keyMappings[GLFW_KEY_G] = KEY_G;
    keyMappings[GLFW_KEY_H] = KEY_H;
    keyMappings[GLFW_KEY_I] = KEY_I;
    keyMappings[GLFW_KEY_J] = KEY_J;
    keyMappings[GLFW_KEY_K] = KEY_K;
    keyMappings[GLFW_KEY_L] = KEY_L;
    keyMappings[GLFW_KEY_M] = KEY_M;
    keyMappings[GLFW_KEY_N] = KEY_N;
    keyMappings[GLFW_KEY_O] = KEY_O;
    keyMappings[GLFW_KEY_P] = KEY_P;
    keyMappings[GLFW_KEY_Q] = KEY_Q;
    keyMappings[GLFW_KEY_R] = KEY_R;
    keyMappings[GLFW_KEY_S] = KEY_S;
    keyMappings[GLFW_KEY_T] = KEY_T;
    keyMappings[GLFW_KEY_Y] = KEY_U;
    keyMappings[GLFW_KEY_V] = KEY_V;
    keyMappings[GLFW_KEY_W] = KEY_W;
    keyMappings[GLFW_KEY_X] = KEY_X;
    keyMappings[GLFW_KEY_Y] = KEY_Y;
    keyMappings[GLFW_KEY_Z] = KEY_Z;
    keyMappings[GLFW_KEY_TAB] = KEY_TAB;
    keyMappings[GLFW_KEY_LEFT_SHIFT] = KEY_LEFT_SHIFT;
    keyMappings[GLFW_KEY_RIGHT_SHIFT] = KEY_RIGHT_SHIFT;
    keyMappings[GLFW_KEY_LEFT_CONTROL] = KEY_LEFT_CTRL;
    keyMappings[GLFW_KEY_RIGHT_CONTROL] = KEY_RIGHT_CTRL;
    keyMappings[GLFW_KEY_LEFT_ALT] = KEY_LEFT_ALT;
    keyMappings[GLFW_KEY_RIGHT_ALT] = KEY_RIGHT_ALT;
    keyMappings[GLFW_KEY_SPACE] = KEY_SPACE;
    keyMappings[GLFW_KEY_ESCAPE] = KEY_ESCAPE;
    keyMappings[GLFW_KEY_BACKSPACE] = KEY_BACKSPACE;
    keyMappings[GLFW_KEY_ENTER] = KEY_ENTER;
    keyMappings[GLFW_KEY_EQUAL] = KEY_EQUALS;
    keyMappings[GLFW_KEY_MINUS] = KEY_MINUS;
    keyMappings[GLFW_KEY_LEFT_BRACKET] = KEY_LEFT_SQUARE_BRACKET;
    keyMappings[GLFW_KEY_RIGHT_BRACKET] = KEY_RIGHT_SQUARE_BRACKET;
    keyMappings[GLFW_KEY_BACKSLASH] = KEY_BACK_SLASH;
    keyMappings[GLFW_KEY_SLASH] = KEY_FORWARD_SLASH;
    keyMappings[GLFW_KEY_COMMA] = KEY_COMMA;
    keyMappings[GLFW_KEY_PERIOD] = KEY_PERIOD;
    keyMappings[GLFW_KEY_INSERT] = KEY_INSERT;
    keyMappings[GLFW_KEY_DELETE] = KEY_DELETE;
    keyMappings[GLFW_KEY_HOME] = KEY_HOME;
    keyMappings[GLFW_KEY_END] = KEY_END;
    keyMappings[GLFW_KEY_PAGE_UP] = KEY_PAGE_UP;
    keyMappings[GLFW_KEY_PAGE_DOWN] = KEY_PAGE_DOWN;
    keyMappings[GLFW_KEY_PRINT_SCREEN] = KEY_PRINT_SCREEN;
    keyMappings[GLFW_KEY_UP] = KEY_UP;
    keyMappings[GLFW_KEY_DOWN] = KEY_DOWN;
    keyMappings[GLFW_KEY_LEFT] = KEY_LEFT;
    keyMappings[GLFW_KEY_RIGHT] = KEY_RIGHT;
    keyMappings[GLFW_KEY_KP_ADD] = KEY_NUMPAD_PLUS;
    keyMappings[GLFW_KEY_KP_0] = KEY_NUMPAD_0;
    keyMappings[GLFW_KEY_KP_1] = KEY_NUMPAD_1;
    keyMappings[GLFW_KEY_KP_2] = KEY_NUMPAD_2;
    keyMappings[GLFW_KEY_KP_3] = KEY_NUMPAD_3;
    keyMappings[GLFW_KEY_KP_4] = KEY_NUMPAD_4;
    keyMappings[GLFW_KEY_KP_5] = KEY_NUMPAD_5;
    keyMappings[GLFW_KEY_KP_6] = KEY_NUMPAD_6;
    keyMappings[GLFW_KEY_KP_7] = KEY_NUMPAD_7;
    keyMappings[GLFW_KEY_KP_8] = KEY_NUMPAD_8;
    keyMappings[GLFW_KEY_KP_9] = KEY_NUMPAD_9;
    keyMappings[GLFW_KEY_F1] = KEY_FUNC_F1;
    keyMappings[GLFW_KEY_F2] = KEY_FUNC_F2;
    keyMappings[GLFW_KEY_F3] = KEY_FUNC_F3;
    keyMappings[GLFW_KEY_F4] = KEY_FUNC_F4;
    keyMappings[GLFW_KEY_F5] = KEY_FUNC_F5;
    keyMappings[GLFW_KEY_F6] = KEY_FUNC_F6;
    keyMappings[GLFW_KEY_F7] = KEY_FUNC_F7;
    keyMappings[GLFW_KEY_F8] = KEY_FUNC_F8;
    keyMappings[GLFW_KEY_F9] = KEY_FUNC_F9;
    keyMappings[GLFW_KEY_F10] = KEY_FUNC_F10;
    keyMappings[GLFW_KEY_F11] = KEY_FUNC_F11;
    keyMappings[GLFW_KEY_F12] = KEY_FUNC_F12;
}

const float Keyboard::getButtonState( const int button ) {
    if ( button < 0 || KEY_LAST <= button ) {
        Trace::message( "Button outside of range." );
        return 0.f;
    }

    return static_cast< float >( m_keyStates[button] );
}

void Keyboard::setButtonState( const int button, const float state ) {
    if ( button < 0 || KEY_LAST <= button ) {
        Trace::message( "Button outside of range." );
    }

    m_keyStates[button] = static_cast< int >( state );
}

} // namespace SquirrelEngine
