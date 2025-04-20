
#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#pragma once

namespace SquirrelEngine {
class Engine;

enum SystemType : unsigned {
    ST_Graphics = 0,
    ST_TimeManager = 1,
};

class System {
public:
    System( Engine* t_engine, const SystemType t_type );
    virtual ~System();

    SystemType getType() const;

protected:
    Engine* m_engine;

private:
    SystemType m_type;
};

} // namespace SquirrelEngine

#endif
