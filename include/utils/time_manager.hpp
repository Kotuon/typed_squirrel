/**
 *
 * @file time_manager.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the TimeManager class, which manages update loops and timing
 * for SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP
#pragma once

#include <chrono>

#include "system.hpp"

namespace SquirrelEngine {
// class Engine; // Fwd declare

/**
 * @brief Manages update loops. Has a regular update and fixed update
 *
 */
class TimeManager : public System {
public:
    /**
     * @brief Construct a new Time Manager object
     *
     */
    TimeManager();

    /**
     * @brief Update time values
     *
     */
    void increment();

    /**
     * @brief Check if fixed time interval has been passed
     *
     * @return true
     * @return false
     */
    bool needsFixedUpdate();

    /**
     * @brief Set lastTime to steady_clock::now
     *
     */
    void resetLastTime();

    /**
     * @brief Return fixed delta time interval
     *
     * @return const float
     */
    const float getFixedDt() const;

    /**
     * @brief Return last non-fixed delta time
     *
     * @return const float
     */
    const float getDeltaTime() const;

    /**
     * @brief Sleeps main thread for given time in milliseconds
     *
     * @param milliseconds
     */
    void sleep( const int milliseconds );

private:
    std::chrono::steady_clock::time_point m_lastTime; //!< last update time
    std::chrono::steady_clock::time_point m_currTime; //!< curr update time
    std::chrono::steady_clock::duration m_timeTaken;  //!< time betwen

    float m_accumulator;           //!< accumulates time since last fixed update
    float m_time;                  //!< total time running
    float m_deltaTime;             //!< last time between updates
    const float m_fixedDt = 0.02f; //!< fixed interval time
};
} // namespace SquirrelEngine

#endif
