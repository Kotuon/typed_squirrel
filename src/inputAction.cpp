
#include "inputAction.hpp"

namespace SquirrelEngine {

InputAction::InputAction() : amount( 0.f ), device( nullptr ) {}

InputAction::InputAction( const std::string t_type, InputDevice* t_device,
                          const float t_amount )
    : type( t_type ), device( t_device ), amount( t_amount ) {}

} // namespace SquirrelEngine
