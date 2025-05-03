
#ifndef ERROR_CODES_HPP
#define ERROR_CODES_HPP
#pragma once

namespace SquirrelEngine {

enum StartupErrors : unsigned {
    SE_Success = 0,
    SE_GLFWFailedInit = 1,
    SE_GraphicsWindowFailedInit = 2,
    SE_SystemFailedInit = 3,
};

} // namespace SquirrelEngine

#endif
