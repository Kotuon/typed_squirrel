
#include <memory>

#include "core.hpp"
#include "utils/crash_handler.hpp"

int main( int, char** ) {
    using namespace SquirrelEngine;

    setupDump();

    std::unique_ptr< Engine > engineInstance = std::make_unique< Engine >();
    if ( engineInstance->initialize() != StartupErrors::SE_Success ) {
        Trace::message( "Failed to start." );
        return EXIT_FAILURE;
    }

    if ( !engineInstance->createSystem< TimeManager >() ) {
        Trace::message( "Failed to create time manager." );
    }

    if ( !engineInstance->createSystem< ShaderManager >() ) {
        Trace::message( "Failed to create shader manager." );
    }

    Window* windowHandle = engineInstance->getWindowHandle();
    windowHandle->create( "SquirrelEngine", 1280, 720, false );

    int frameWidth, frameHeight;
    windowHandle->frameBufferSize( frameWidth, frameHeight );

    std::unique_ptr< World > worldInstance = std::make_unique< World >();
    Entity* camera = worldInstance->createEntity( "Main camera" );
    CameraComponent* cameraComp = camera->createComponent< CameraComponent >();

    cameraComp->aspect = static_cast< float >( frameWidth ) /
                         static_cast< float >( frameHeight );
    cameraComp->transform.setPosition( vector3( 50.f, 30.f, 50.f ) );
    cameraComp->transform.rotate( vector3( 0.f, 1.f, 0.f ),
                                  glm::radians( 45.f ) );
    cameraComp->transform.rotate( vector3( 1.f, 0.f, 0.f ),
                                  glm::radians( -20.f ) );

    engineInstance->update( worldInstance.get() );
    engineInstance->shutdown();

    return EXIT_SUCCESS;
}
