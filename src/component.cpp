
#include "component.hpp"
#include "entity.hpp"

namespace SquirrelEngine {

Component::Component() {}

Component::Component( Entity* t_parent ) : parent( t_parent ) {}

} // namespace SquirrelEngine
