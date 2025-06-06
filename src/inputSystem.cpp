/**
 *
 * @file inputSystem.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the InputSystem class, which manages input devices, action
 * mappings, and input events in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "engine.hpp"
#include "eventSystem.hpp"
#include "inputAction.hpp"
#include "inputSystem.hpp"

namespace SquirrelEngine {

/**
 * @brief Updates the input system and all input devices.
 * @param delta Time elapsed since last update.
 */
void InputSystem::update( const float ) {
    for ( auto it = m_devices.begin(); it != m_devices.end(); ++it ) {
        ( *it )->update();
    }
}

/**
 * @brief Finds an input device by type and optional offset.
 * @param type The device type (see InputDeviceType).
 * @param offset Index offset for multiple devices of the same type.
 * @return Pointer to the found input device, or nullptr if not found.
 */
InputDevice* InputSystem::findInputDevice( const int type, const int offset ) {
    int counter = 0;

    for ( auto it = m_devices.begin(); it != m_devices.end(); ++it ) {
        InputDevice* device = ( *it ).get();
        if ( device->getType() == type ) {
            if ( counter == offset ) {
                return device;
            }
            counter += 1;
        }
    }

    return nullptr;
}

/**
 * @brief Registers an action mapping for a device and button.
 * @param device Pointer to the input device.
 * @param button Button index.
 * @param name Name of the action.
 */
void InputSystem::registerActionMapping( InputDevice* device, const int button,
                                         const std::string name ) {
    auto it = m_actions.find( name );
    if ( it == m_actions.end() ) {
        m_actions[name] = std::vector< std::unique_ptr< ActionMapping > >();
    }

    m_actions[name].emplace_back(
        std::make_unique< ActionMapping >( name, device, button ) );
    m_deviceActions[device].push_back( m_actions[name].back().get() );
}

/**
 * @brief Triggers an action for a device and button with a given amount.
 * @param device Pointer to the input device.
 * @param button Button index.
 * @param amount Value or amount of the action.
 */
void InputSystem::triggerAction( InputDevice* device, const int button,
                                 const float amount ) {
    EventSystem* eventSystem = owner->getSystem< EventSystem >();

    auto actionMappingIt = m_deviceActions.find( device );
    if ( actionMappingIt == m_deviceActions.end() ) {
        return;
    }

    auto& actionList = actionMappingIt->second;

    for ( auto it = actionList.begin(); it != actionList.end(); ++it ) {
        ActionMapping* mapping = ( *it );

        if ( mapping->device == device && mapping->button == button ) {
            eventSystem->publish( std::make_unique< InputAction >(
                                      mapping->action, device, amount )
                                      .get() );
        }
    }
}

/**
 * @brief Gets the current state of an action.
 * @param action Name of the action.
 * @return The state of the action as a float.
 */
const float InputSystem::getActionState( const std::string action ) {
    auto thisAction = m_actions.find( action );
    if ( thisAction == m_actions.end() ) {
        return 0.f;
    }

    auto& mappingList = thisAction->second;

    float value = 0.f;
    for ( auto it = mappingList.begin(); it != mappingList.end(); ++it ) {
        ActionMapping* mapping = ( *it ).get();
        value += mapping->device->getButtonState( mapping->button );
    }

    return value;
}

} // namespace SquirrelEngine
