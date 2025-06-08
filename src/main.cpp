
#include <memory>

#include "core.hpp"
#include "utils/crash_handler.hpp"

////////////////////////////////////////////////////////////////////////////////
#include "tests/glmQuaternionTests.hpp"
#include "tests/quaternionTests.hpp"
#include "utils/timer.hpp"

void compareQuats() {
    using namespace SquirrelEngine;

    QuatTests::init();
    QuatTests::construction();
    QuatTests::copyConstruct();
    QuatTests::assignment();
    QuatTests::addAssign();
    QuatTests::subAssign();
    QuatTests::mulQuatAssign();
    QuatTests::mulScaleAssign();
    QuatTests::negation();
    QuatTests::add();
    QuatTests::sub();
    QuatTests::mulQuat();
    QuatTests::mulScale();
    QuatTests::dot();
    QuatTests::norm();
    QuatTests::normSquared();
    QuatTests::normalize();
    QuatTests::conjugate();
    QuatTests::rotateVectorFromFloats();
    QuatTests::rotateVectorFromArray();
    QuatTests::fromEuler();
    QuatTests::fromAxisAngle();
    QuatTests::end();

    GLMQuatTests::init();
    GLMQuatTests::construction();
    GLMQuatTests::copyConstruct();
    GLMQuatTests::assignment();
    GLMQuatTests::addAssign();
    GLMQuatTests::subAssign();
    GLMQuatTests::mulQuatAssign();
    GLMQuatTests::mulScaleAssign();
    GLMQuatTests::negation();
    GLMQuatTests::add();
    GLMQuatTests::sub();
    GLMQuatTests::mulQuat();
    GLMQuatTests::mulScale();
    GLMQuatTests::dot();
    GLMQuatTests::norm();
    GLMQuatTests::normSquared();
    GLMQuatTests::normalize();
    GLMQuatTests::conjugate();
    GLMQuatTests::rotateVectorFromFloats();
    GLMQuatTests::rotateVectorFromArray();
    GLMQuatTests::fromEuler();
    GLMQuatTests::fromAxisAngle();
    GLMQuatTests::end();
}

int main( int, char** ) {
    using namespace SquirrelEngine;
    setupDump();
    compareQuats();
}
////////////////////////////////////////////////////////////////////////////////

// int main( int, char** ) {
//     using namespace SquirrelEngine;

//     setupDump();

//     Engine* engineInstance = Engine::instance();
//     if ( engineInstance->initialize() != StartupErrors::SE_Success ) {
//         Trace::message( "Failed to start." );
//         return EXIT_FAILURE;
//     }

//     Window* windowHandle = engineInstance->getWindowHandle();
//     windowHandle->create( "SquirrelEngine", 1280, 720, false );

//     int frameWidth, frameHeight;
//     windowHandle->frameBufferSize( frameWidth, frameHeight );

//     // Init inputs
//     InputSystem* inputSystem = engineInstance->createSystem< InputSystem >();
//     if ( !inputSystem ) {
//         Trace::message( "Failed to create input system." );
//     }

//     // Keyboard setup
//     Keyboard* keyboard = inputSystem->createInputDevice< Keyboard >();
//     keyboard->initialize();

//     // Movement binds
//     inputSystem->registerActionMapping( keyboard, KEY_W, "move forward" );
//     inputSystem->registerActionMapping( keyboard, KEY_S, "move backward" );
//     inputSystem->registerActionMapping( keyboard, KEY_A, "move left" );
//     inputSystem->registerActionMapping( keyboard, KEY_D, "move right" );
//     inputSystem->registerActionMapping( keyboard, KEY_E, "move up" );
//     inputSystem->registerActionMapping( keyboard, KEY_Q, "move down" );

//     inputSystem->registerActionMapping( keyboard, KEY_LEFT_SHIFT,
//                                         "enable camera movement" );

//     // Engine binds
//     inputSystem->registerActionMapping( keyboard, KEY_ESCAPE, "close window"
//     );

//     // Mouse setup
//     inputSystem->createInputDevice< Mouse >();

//     World* worldInstance = World::instance();
//     Entity* camera = worldInstance->createEntity( "Main camera" );
//     CameraComponent* cameraComp = camera->createComponent< CameraComponent
//     >();

//     cameraComp->aspect = static_cast< float >( frameWidth ) /
//                          static_cast< float >( frameHeight );
//     cameraComp->transform.setPosition( vector3( 0.f, 0.f, 20.f ) );

//     Entity* cube = worldInstance->createEntity( "Cube01" );
//     Model* cubeModel = cube->createComponent< Model >();
//     cubeModel->initMesh( "models/cube.obj" );
//     cubeModel->initShader( "shaders/base.vert", "shaders/base.frag" );
//     // cube->transform.setScale( vector3( 0.5f ) );

//     engineInstance->update();
//     engineInstance->shutdown();

//     return EXIT_SUCCESS;
// }
