
#include <memory>

#include "core.hpp"
#include "utils/crash_handler.hpp"

int main( int, char** ) {
    using namespace SquirrelEngine;

    setupDump();

    std::unique_ptr< Engine > engineInstance = std::make_unique< Engine >();

    const StartupErrors result = engineInstance->initialize();

    if ( result != SE_Success ) {
        return EXIT_FAILURE;
    }

    engineInstance->update();
    engineInstance->shutdown();

    return 0;
}
