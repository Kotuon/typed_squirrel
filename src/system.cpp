
#include "core.hpp"

namespace SquirrelEngine {

System::System( Engine* t_engine, const SystemType t_type )
    : m_engine( t_engine ), m_type( t_type ) {}

System::~System() {}

StartupErrors System::initialize() { return SE_Success; }

void System::update() {}

void System::shutdown() {}

SystemType System::getType() const { return m_type; }

} // namespace SquirrelEngine
