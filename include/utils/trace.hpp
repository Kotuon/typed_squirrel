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

#define FILENAME __FILE__
#define LINENUMBER __LINE__

// std includes //
#include <string>
#include <fstream>
#include <source_location>

namespace SquirrelEngine {

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

} // namespace SquirrelEngine

#endif
