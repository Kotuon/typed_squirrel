
#ifndef TIMER_HPP
#define TIMER_HPP
#pragma once

#include <chrono>
#include <string>
#include <fmt/core.h>
#include <typeinfo>
#include <fstream>
#include <source_location>

namespace SquirrelEngine {

struct Timer {
    std::chrono::time_point< std::chrono::steady_clock > Start;
    std::chrono::time_point< std::chrono::steady_clock > End;
    std::chrono::duration< double, std::micro > Duration;

    std::fstream TraceStream; //!< Output file

    void openFile( const std::string TestName );
    void saveFile();

    template < typename TCallback >
    void run( TCallback&& Callback,
              std::source_location Src = std::source_location::current() ) {
        start();

        Callback();

        end( Src );
    }

    void start();
    void end( std::source_location Src );
};

} // namespace SquirrelEngine

#endif
