/**
 *
 * @file engine.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Class for handing startup, update, and shutdown of engine
 * @date 2025-04-20
 *
 */

#ifndef ENGINE_HPP
#define ENGINE_HPP
#pragma once

#include <memory>
#include <string>

namespace SquirrelEngine {
// Forward declarations of enums
enum StartupErrors : unsigned;
enum SystemType : unsigned;

// Forward declarations of classes
class System;
class SystemContainer;
class TimeManager;

class Engine {
public:
    virtual ~Engine();

    /**
     * @brief Starts all essential systems for the engine
     *
     * @return true Successfully started engine
     * @return false Failed to start engine
     */
    enum StartupErrors initialize();

    /**
     * @brief Handles updates for all systems in engine
     *
     */
    void update();

    /**
     * @brief Properly shuts all systems down on engine close
     *
     */
    void shutdown();

private:
    std::unique_ptr<SystemContainer> m_systemContainer;

    bool m_isRunning = false; //!< If update loop is currently running
};

} // namespace SquirrelEngine
#endif
