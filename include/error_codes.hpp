/**
 *
 * @file error_codes.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Defines error codes used for engine startup routines in SquirrelEngine
 * @date 2025-06-06
 *
 */

#ifndef ERROR_CODES_HPP
#define ERROR_CODES_HPP
#pragma once

namespace SquirrelEngine {

/**
 * @brief Error codes for engine startup routines.
 */
enum StartupErrors : unsigned {
    SE_Success = 0,                  //!< Startup completed successfully.
    SE_GLFWFailedInit = 1,           //!< Failed to initialize GLFW.
    SE_GraphicsWindowFailedInit = 2, //!< Failed to initialize graphics window.
    SE_SystemFailedInit = 3,         //!< Failed to initialize a system.
};

} // namespace SquirrelEngine

#endif
