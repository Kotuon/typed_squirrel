/**
 *
 * @file time_manager.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the TimeManager class, which manages update loops and
 * timing for SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <thread>

#include "utils/time_manager.hpp"

namespace SquirrelEngine {

using namespace std::chrono;

/**
 * @brief Construct a new Time Manager object
 *
 */
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

/**
 * @brief Check if fixed time interval has been passed
 *
 * @return true
 * @return false
 */
bool TimeManager::needsFixedUpdate() {
    const bool result = m_accumulator >= m_fixedDt;

    if ( result ) {
        m_accumulator -= m_fixedDt;
        m_time += m_fixedDt;
    }

    return result;
}

/**
 * @brief Set lastTime to steady_clock::now
 *
 */
void TimeManager::resetLastTime() { m_lastTime = steady_clock::now(); }

/**
 * @brief Return fixed delta time interval
 *
 * @return const float
 */
const float TimeManager::getFixedDt() const { return m_fixedDt; }

/**
 * @brief Return last non-fixed delta time
 *
 * @return const float
 */
const float TimeManager::getDeltaTime() const { return m_deltaTime; }

/**
 * @brief Sleeps main thread for given time in milliseconds
 *
 * @param milliseconds
 */
void TimeManager::sleep( const int milliseconds ) {
    std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
}

} // namespace SquirrelEngine
