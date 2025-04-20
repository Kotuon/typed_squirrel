
#include "core.hpp"

namespace SquirrelEngine {

System::System( Engine* t_engine, const SystemType t_type )
    : m_engine( t_engine ), m_type( t_type ) {}

System::~System() {}

SystemType System::getType() const { return m_type; }

} // namespace SquirrelEngine
