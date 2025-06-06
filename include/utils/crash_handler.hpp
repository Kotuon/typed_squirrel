/**
 *
 * @file crash_handler.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares utilities for handling application crashes and writing dump
 * files in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef CRASH_HANDLER
#define CRASH_HANDLER

namespace SquirrelEngine {

/**
 * @brief Setup up writing of dump file in case of crash
 *
 */
void setupDump();

} // namespace SquirrelEngine

#endif CRASH_HANDLER
