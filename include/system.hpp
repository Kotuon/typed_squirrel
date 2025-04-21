
#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#pragma once

namespace SquirrelEngine {
// Forward declarations of enums
enum StartupErrors : unsigned;

// Forward declarations of classes
class Engine;

enum SystemType : unsigned {
    ST_Graphics = 0,
    ST_TimeManager = 1,
};

class System {
public:
    System( Engine* t_engine, const SystemType t_type );
    virtual ~System();

    virtual StartupErrors initialize();
    virtual void update();
    virtual void shutdown();

    SystemType getType() const;

protected:
    Engine* m_engine;

private:
    SystemType m_type;
};

} // namespace SquirrelEngine

#endif
