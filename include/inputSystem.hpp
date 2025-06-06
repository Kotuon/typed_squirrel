/**
 *
 * @file inputSystem.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the InputSystem class, which manages input devices, action
 * mappings, and input events in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP
#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "inputDevice.hpp"
#include "system.hpp"

namespace SquirrelEngine {

/**
 * @brief The InputSystem class manages input devices, action mappings, and
 * input events.
 */
class InputSystem : public System {
public:
    /**
     * @brief Default constructor for InputSystem.
     */
    InputSystem() = default;

    /**
     * @brief Default destructor for InputSystem.
     */
    ~InputSystem() = default;

    /**
     * @brief Updates the input system and all input devices.
     * @param delta Time elapsed since last update.
     */
    void update( const float delta );

    /**
     * @brief Creates and initializes a new input device of type T.
     * @tparam T InputDevice subclass.
     * @return Pointer to the created input device.
     */
    template < class T > T* createInputDevice() {
        m_devices.emplace_back( std::make_unique< T >() );

        auto& newDevice = m_devices.back();
        newDevice->initialize();

        return dynamic_cast< T* >( newDevice.get() );
    }

    /**
     * @brief Finds the first input device of type T, with optional offset.
     * @tparam T InputDevice subclass.
     * @param offset Index offset for multiple devices of the same type.
     * @return Pointer to the found input device, or nullptr if not found.
     */
    template < class T > T* findInputDevice( const int offset = 0 ) {
        int counter = 0;

        for ( auto it = m_devices.begin(); it != m_devices.end(); ++it ) {
            T* device = dynamic_cast< T* >( ( *it ).get() );
            if ( device ) {
                if ( counter == offset ) {
                    return device;
                }
                counter += 1;
            }
        }

        return nullptr;
    }

    /**
     * @brief Finds an input device by type and optional offset.
     * @param type The device type (see InputDeviceType).
     * @param offset Index offset for multiple devices of the same type.
     * @return Pointer to the found input device, or nullptr if not found.
     */
    InputDevice* findInputDevice( const int type, const int offset = 0 );

    /**
     * @brief Registers an action mapping for a device and button.
     * @param device Pointer to the input device.
     * @param button Button index.
     * @param name Name of the action.
     */
    void registerActionMapping( InputDevice* device, const int button,
                                const std::string name );

    /**
     * @brief Triggers an action for a device and button with a given amount.
     * @param device Pointer to the input device.
     * @param button Button index.
     * @param amount Value or amount of the action.
     */
    void triggerAction( InputDevice* device, const int button,
                        const float amount );

    /**
     * @brief Gets the current state of an action.
     * @param action Name of the action.
     * @return The state of the action as a float.
     */
    const float getActionState( const std::string action );

protected:
    /**
     * @brief Structure representing an action mapping.
     */
    struct ActionMapping {
        /**
         * @brief Constructs an ActionMapping.
         * @param t_name Name of the action.
         * @param t_device Pointer to the input device.
         * @param t_button Button index.
         */
        ActionMapping( const std::string t_name, InputDevice* t_device,
                       const int t_button )
            : action( t_name ), device( t_device ), button( t_button ) {}

        std::string action;  //!< Name of the action.
        InputDevice* device; //!< Pointer to the input device.
        int button;          //!< Button index.
    };

    std::vector< std::unique_ptr< InputDevice > >
        m_devices; //!< List of input devices.

    std::unordered_map< std::string,
                        std::vector< std::unique_ptr< ActionMapping > > >
        m_actions; //!< Map of action names to their mappings.

    std::unordered_map< InputDevice*, std::vector< ActionMapping* > >
        m_deviceActions; //!< Map of devices to their action mappings.
};

} // namespace SquirrelEngine

#endif
