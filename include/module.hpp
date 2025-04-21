
#ifndef MODULE_HPP
#define MODULE_HPP
#pragma once

namespace SquirrelEngine {
// Forward declarations of enums
enum StartupErrors : unsigned;

// Forward declarations of classes
class Engine;

enum ModuleType : unsigned {
    MT_Graphics = 0,
    MT_TimeManager = 1,
};

class Module {
public:
    Module( Engine* t_engine, const ModuleType t_type );
    virtual ~Module();

    virtual StartupErrors initialize();
    virtual void update();
    virtual void shutdown();

    ModuleType getType() const;

protected:
    Engine* m_engine;

private:
    ModuleType m_type;
};

} // namespace SquirrelEngine

#endif
