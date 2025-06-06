/**
 *
 * @file time_manager.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-06
 *
 */

#include <thread>

#include "utils/time_manager.hpp"

namespace SquirrelEngine {

using namespace std::chrono;

TimeManager::TimeManager()
    : m_lastTime( steady_clock::now() ), m_accumulator( 0.f ), m_time( 0.f ),
      m_deltaTime( 0.f ) {}

void TimeManager::increment() {
    m_currTime = steady_clock::now();
    m_timeTaken = m_currTime - m_lastTime;
    m_deltaTime = static_cast< float >( m_timeTaken.count() ) *
                  steady_clock::period::num / steady_clock::period::den;
    m_lastTime = m_currTime;
    m_accumulator += m_deltaTime;
}

bool TimeManager::needsFixedUpdate() {
    const bool result = m_accumulator >= m_fixedDt;

    if ( result ) {
        m_accumulator -= m_fixedDt;
        m_time += m_fixedDt;
    }

    return result;
}

void TimeManager::resetLastTime() { m_lastTime = steady_clock::now(); }

const float TimeManager::getFixedDt() const { return m_fixedDt; }

const float TimeManager::getDeltaTime() const { return m_deltaTime; }

void TimeManager::sleep( const int milliseconds ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
}

} // namespace SquirrelEngine
