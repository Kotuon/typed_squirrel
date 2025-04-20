
#ifndef PROFILER_HPP
#define PROFILER_HPP
#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace SquirrelEngine {
class Profiler {
public:
    Profiler();
    Profiler( size_t HitTotal_ );
    ~Profiler();

    void record();
    void startFile();
    void closeFile();

private:
    std::chrono::time_point< std::chrono::steady_clock > Start;
    std::chrono::time_point< std::chrono::steady_clock > Current;

    std::thread WorkerThread;

    struct InteralProfiler;
    std::unique_ptr< InteralProfiler > IntProfiler;

    size_t HitTotal = 10000;

    bool HasWritten = false;
    bool Exit = false;
};
} // namespace SquirrelEngine

#endif
