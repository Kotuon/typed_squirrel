/**
 *
 * @file trace.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Provides the Trace class for logging messages to an output file and
 * console in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef TRACE_HPP
#define TRACE_HPP
#pragma once

#include "fmt/format.h"
#include "fmt/ranges.h"

// std includes //
#include <fstream>
#include <iostream>
#include <source_location>
#include <string>

struct FormatWithSource {
    const char* str;
    std::source_location src;

    FormatWithSource( const char* str_, std::source_location src_ =
                                            std::source_location::current() )
        : str( str_ ), src( src_ ) {}
};

/*! Trace class */
class Trace {
public:
    /**
     * @brief Prints a message into the output file and console
     *
     * @param message Message to be printed
     * @param src Source location information
     * @return void
     */
    static void
    message( std::string Message,
             std::source_location Src = std::source_location::current() );

    template < typename... Args >
    static void message( FormatWithSource fmt, Args&&... args ) {
        Trace& TraceInstance = Trace::getInstance();
        if ( !TraceInstance.TraceStream ) return;

        std::string Filename = std::string( fmt.src.file_name() );

        size_t startPos = Filename.find_last_of( '\\' );
        if ( startPos == std::string::npos ) startPos = 0;

        std::string Message = fmt::format( fmt::runtime( fmt.str ), args... );

        std::string output = Filename.substr( startPos, std::string::npos ) +
                             "( " + std::to_string( fmt.src.line() ) + ":" +
                             std::to_string( fmt.src.column() ) + " )" + ": " +
                             Message;

        TraceInstance.TraceStream << output << "\n";
        std::cout << output << "\n";
    }

    /**
     * @brief Close output file
     *
     */
    ~Trace();

private:
    /**
     * @brief Construct a new Trace:: Trace object
     *
     */
    Trace();

    /**
     * @brief Get the instance of trace
     *
     * @return Trace&
     */
    static Trace& getInstance() {
        static Trace TraceInstance;
        return TraceInstance;
    }

private:
    std::fstream TraceStream; //!< Output file
};

#endif