
#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP
#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "inputDevice.hpp"
#include "system.hpp"

namespace SquirrelEngine {

class InputSystem : public System {
    InputSystem() = default;
    ~InputSystem() = default;

    void update( const float delta );

    template < class T > T* createInputDevice() {
        m_devices.emplace_back( std::make_unique< InputDevice >() );

        auto newDevice = m_devices.back();
        newDevice->initialize();

        return newDevice.get();
    }

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

    InputDevice* findInputDevice( const int type, const int offset = 0 );

    void registerActionMapping( InputDevice* device, const int button,
                                const std::string name );

    void triggerAction( InputDevice* device, const int button,
                        const float amount );

    const float getActionState( const std::string action );

protected:
    struct ActionMapping {
        ActionMapping( const std::string t_name, InputDevice* t_device,
                       const int t_button )
            : action( t_name ), device( t_device ), button( t_button ) {}

        std::string action;
        InputDevice* device;
        int button;
    };

    std::vector< std::unique_ptr< InputDevice > > m_devices;

    std::unordered_map< std::string,
                        std::vector< std::unique_ptr< ActionMapping > > >
        m_actions;

    std::unordered_map< InputDevice*, std::vector< ActionMapping* > >
        m_deviceActions;
};

} // namespace SquirrelEngine

#endif
