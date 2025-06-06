/**
 *
 * @file crash_handler.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements utilities for handling application crashes and writing dump
 * files in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include <Windows.h>
#include <dbghelp.h>

#pragma comment( lib, "dbghelp.lib" )

#include "utils/crash_handler.hpp"

namespace SquirrelEngine {

/**
 * @brief Writes dump file if program crashes
 *
 * @param Exception
 * @return LONG
 */
LONG WINAPI writeDump( EXCEPTION_POINTERS* Exception ) {
    MINIDUMP_EXCEPTION_INFORMATION Information = MINIDUMP_EXCEPTION_INFORMATION{
        GetCurrentThreadId(), Exception, FALSE };

    MiniDumpWriteDump(
        GetCurrentProcess(), GetCurrentProcessId(),
        CreateFileA( "crash_mini.dmp", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL, NULL ),
        MINIDUMP_TYPE( MiniDumpNormal | MiniDumpWithDataSegs |
                       MiniDumpWithCodeSegs |
                       MiniDumpWithIndirectlyReferencedMemory |
                       MiniDumpWithUnloadedModules | MiniDumpWithFullMemory ),
        &Information, NULL, NULL );

    return EXCEPTION_CONTINUE_SEARCH;
}

/**
 * @brief Setup up writing of dump file in case of crash
 *
 */
void setupDump() {
    ULONG GuaranteedStackSize = 17000;
    SetUnhandledExceptionFilter( writeDump );
    SetThreadStackGuarantee( &GuaranteedStackSize );
}

} // namespace SquirrelEngine
