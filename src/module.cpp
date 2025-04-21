
#include "core.hpp"

namespace SquirrelEngine {

Module::Module( Engine* t_engine, const ModuleType t_type )
    : m_engine( t_engine ), m_type( t_type ) {}

Module::~Module() {}

StartupErrors Module::initialize() { return SE_Success; }

void Module::update() {}

void Module::shutdown() {}

ModuleType Module::getType() const { return m_type; }

} // namespace SquirrelEngine
