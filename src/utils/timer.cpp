/**
 *
 * @file timer.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @date 2025-06-07
 *
 */

#include "utils/timer.hpp"

namespace SquirrelEngine {

void Timer::openFile( const std::string TestName ) {
    TraceStream.open( TestName + ".csv", std::ofstream::out );
    TraceStream << "File name, Function name, Time taken\n";
}

void Timer::saveFile() {
    if ( TraceStream ) TraceStream.close();
}

void Timer::start() { Start = std::chrono::steady_clock::now(); }

void Timer::end( std::source_location Src ) {
    End = std::chrono::steady_clock::now();
    Duration = End - Start;

    std::string Filename = std::string( Src.file_name() );

    size_t startPos1 = Filename.find_last_of( '\\' );
    if ( startPos1 == std::string::npos ) startPos1 = 0;

    std::string FunctionName = std::string( Src.function_name() );

    size_t startPos2 = FunctionName.find_last_of( "::" );
    if ( startPos2 == std::string::npos ) startPos2 = 0;

    TraceStream << Filename.substr( startPos1 + 1, std::string::npos ) + ","
                << FunctionName.substr( startPos2 + 1, std::string::npos ) + ","
                << Duration.count() << "\n";
}

} // namespace SquirrelEngine
