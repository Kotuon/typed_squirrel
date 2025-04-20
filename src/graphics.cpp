
#include "core.hpp"

namespace SquirrelEngine {

Graphics::Graphics( Engine* t_engine )
    : System( t_engine, SystemType::ST_Graphics ) {}

Graphics::~Graphics() {}

SystemType Graphics::getType() { return SystemType::ST_Graphics; }

} // namespace SquirrelEngine
