

#include <Windows.h>
#include <dbghelp.h>

#pragma comment( lib, "dbghelp.lib" )

#include "utils/crash_handler.hpp"

namespace SquirrelEngine {

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

void setupDump() {
    ULONG GuaranteedStackSize = 17000;
    SetUnhandledExceptionFilter( writeDump );
    SetThreadStackGuarantee( &GuaranteedStackSize );
}

} // namespace SquirrelEngine
