
#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP
#pragma once

#include <chrono>
#include "system.hpp"

namespace SquirrelEngine {
class Engine;

class TimeManager : public System {
public:
    TimeManager( Engine* t_engine );

    void increment();
    bool needsFixedUpdate();

    void resetLastTime();

    const float getFixedDt() const;
    const float getDeltaTime() const;

    static SystemType getType();

private:
    std::chrono::steady_clock::time_point m_lastTime;
    std::chrono::steady_clock::time_point m_currTime;
    std::chrono::steady_clock::duration m_timeTaken;
    float m_accumulator;
    float m_time;
    float m_deltaTime;
    const float m_fixedDt = 0.02f;
};
} // namespace SquirrelEngine

#endif
