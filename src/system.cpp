
#include <functional>

#include "engine.hpp"
#include "system.hpp"

namespace SquirrelEngine {

StartupErrors System::initialize( Engine* t_owner ) {
    owner = t_owner;

    owner->addUpdateCallback(
        std::bind( &System::update, this, std::placeholders::_1 ) );

    return StartupErrors::SE_Success;
}

} // namespace SquirrelEngine
