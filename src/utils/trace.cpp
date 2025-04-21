
// std includes //
#include <iostream>
#include <cstdarg>

// Engine includes //
#include "utils/trace.hpp"

namespace SquirrelEngine {
Trace::Trace() {
    TraceStream.open( "trace.log", std::ofstream::out );
    if ( !TraceStream ) std::cout << "Trace file wasn't opened successfully.\n";

    std::source_location Src = std::source_location::current();
    std::cout << "trace.cpp" << "( " << std::to_string( Src.line() ) << ":"
              << std::to_string( Src.column() ) + " )" << ": "
              << "Trace file was opened successfully.\n";
}

void Trace::message( std::string Message, std::source_location Src ) {
    Trace& TraceInstance = Trace::getInstance();
    if ( !TraceInstance.TraceStream ) return;

    std::string Filename = std::string( Src.file_name() );

    size_t startPos = Filename.find_last_of( '\\' );
    if ( startPos == std::string::npos ) startPos = 0;

    std::string output = Filename.substr( startPos + 1, std::string::npos ) +
                         "( " + std::to_string( Src.line() ) + ":" +
                         std::to_string( Src.column() ) + " )" + ": " + Message;

    TraceInstance.TraceStream << output << "\n";
    std::cout << output << "\n";
}

Trace::~Trace() {
    if ( TraceStream ) TraceStream.close();
}

} // namespace SquirrelEngine
