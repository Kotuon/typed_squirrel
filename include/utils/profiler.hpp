/**
 *
 * @file profiler.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-06
 *
 */

#ifndef PROFILER_HPP
#define PROFILER_HPP
#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace SquirrelEngine {

/**
 * @brief Profilier that takes snapshots. Outputs csv of hits.
 *
 */
class Profiler {
public:
    /**
     * @brief Sets up threads and timing for profilier.
     *
     */
    Profiler();

    /**
     * @brief Sets up threads and timing for profilier with custom hit total.
     *
     */
    Profiler( size_t HitTotal_ );

    /**
     * @brief Closes thread if still running function. Gets Symbol info and
     * prints to file.
     *
     */
    ~Profiler();

    /**
     * @brief Recording EIP every 1 ms
     *
     */
    void record();

    /**
     * @brief Setting up output file.
     *
     */
    void startFile();

    /**
     * @brief Closes output file
     *
     */
    void closeFile();

private:
    std::chrono::time_point< std::chrono::steady_clock > Start;
    std::chrono::time_point< std::chrono::steady_clock > Current;

    std::thread WorkerThread; //!< Waits for 1ms then takes snapshot

    struct InteralProfiler; //!< Fwd decalring internal struct
    std::unique_ptr< InteralProfiler > IntProfiler;

    size_t HitTotal = 10000; //!< Default amount of snapshots

    bool HasWritten = false; //!< Whether output has been written yet
    bool Exit = false;       //!< If program is exiting before finished
};

} // namespace SquirrelEngine

#endif
