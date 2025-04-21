

#include <Windows.h>
#include <dbghelp.h>

#include "utils/profiler.hpp"

namespace SquirrelEngine {

struct Profiler::InteralProfiler {

    /**
     * @brief Getting symbol info from EIP
     *
     * @param address EIP
     * @param buff    Buffer for symbol information
     * @return PSYMBOL_INFO
     */
    PSYMBOL_INFO getSymbol( DWORD64 Address, PSYMBOL_INFO Buff ) {
        PDWORD64 Displacement = 0;
        PSYMBOL_INFO Symbol = ( PSYMBOL_INFO )Buff;
        Symbol->SizeOfStruct = sizeof( SYMBOL_INFO );
        Symbol->MaxNameLen = MAX_SYM_NAME;
        SymFromAddr( GetCurrentProcess(), Address, Displacement, Symbol );
        return Symbol;
    }

    /**
     * @brief Searches for occurance of function in function list.
     *
     * @param functionList List of identified functions
     * @param name         Name of function to search
     * @param nameLen      Length of name
     * @return int         Location of function in list (-1 if not found)
     */
    int find( std::vector< std::tuple< DWORD64, char*, int > >& FunctionList,
              char* Name, int NameLen ) {
        // Looking through list for function name
        for ( int i = 0; i < FunctionList.size(); ++i ) {
            char* CurrentItemName = std::get< 1 >( FunctionList[i] );
            bool IsSame = true;

            // Comparing names
            for ( int j = 0; j < NameLen; ++j ) {
                if ( CurrentItemName[j] != Name[j] ) {
                    IsSame = false;
                    break;
                }
            }
            if ( IsSame ) return i;
        }
        return -1;
    }

    void writeMessage( std::tuple< DWORD64, char*, int >& FunctionInfo ) {
        float HitCount = ( float )std::get< 2 >( FunctionInfo );
        float TotalHits = ( float )EipList.size();
        float HitPercentage = ( HitCount / TotalHits ) * 100.f;

        fprintf( DebugFile, "%s,%i,%f%%\n", std::get< 1 >( FunctionInfo ),
                 std::get< 2 >( FunctionInfo ), HitPercentage );
    }

    std::vector< CONTEXT > EipList;
    HANDLE MainThread;

    FILE* DebugFile = nullptr;
};

/**
 * @brief Sets up threads and timing for profilier.
 *
 */
Profiler::Profiler() {
    IntProfiler = std::make_unique< InteralProfiler >();

    IntProfiler->MainThread = OpenThread(
        THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION,
        0, GetCurrentThreadId() );

    Start = std::chrono::steady_clock::now();
    WorkerThread = std::thread( &Profiler::record, this );
}

/**
 * @brief Sets up threads and timing for profilier with custom hit total.
 *
 */
Profiler::Profiler( const size_t HitTotal_ ) : HitTotal( HitTotal_ ) {
    IntProfiler = std::make_unique< InteralProfiler >();

    IntProfiler->MainThread = OpenThread(
        THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION,
        0, GetCurrentThreadId() );

    Start = std::chrono::steady_clock::now();
    WorkerThread = std::thread( &Profiler::record, this );
}

/**
 * @brief Closes thread if still running function. Gets Symbol info and prints
 *        to file.
 *
 */
Profiler::~Profiler() {
    // Closing thread
    Exit = true;
    WorkerThread.join();

    startFile();

    // Setting up symbol information
    SymSetOptions( SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS );
    if ( !SymInitialize( GetCurrentProcess(), NULL, true ) ) return;

    // Condensing common items to new list
    std::vector< std::tuple< DWORD64, char*, int > > FunctionList;
    for ( int i = 0; i < IntProfiler->EipList.size(); ++i ) {
        ULONG64 buff[( sizeof( SYMBOL_INFO ) + MAX_SYM_NAME * sizeof( TCHAR ) +
                       sizeof( ULONG64 ) - 1 ) /
                     sizeof( ULONG64 )];
        PSYMBOL_INFO symbols = IntProfiler->getSymbol(
            IntProfiler->EipList[i].Rip, ( PSYMBOL_INFO )buff );

        size_t NameLen = symbols->NameLen;
        char* Name = new char[NameLen + 3];
        Name[0] = '"';
        for ( size_t j = 1; j < NameLen + 1; ++j ) {
            Name[j] = *( symbols->Name + j - 1 );
        }
        Name[symbols->NameLen + 1] = '"';
        Name[symbols->NameLen + 2] = '\0';

        // Checking if it's new function
        int result =
            IntProfiler->find( FunctionList, Name, symbols->NameLen + 3 );
        if ( result == -1 ) {

            FunctionList.push_back(
                std::make_tuple( IntProfiler->EipList[i].Rip, Name, 1 ) );
        } else {
            std::get< 2 >( FunctionList[result] ) += 1;
            delete[] Name;
        }
    }

    // Writing output file
    for ( int i = 0; i < FunctionList.size(); ++i ) {
        IntProfiler->writeMessage( FunctionList[i] );
        delete[] std::get< 1 >( FunctionList[i] );
    }

    closeFile();
}

/**
 * @brief Recording EIP every 1 ms
 *
 */
void Profiler::record() {
    while ( true ) {
        if ( Exit ) return;

        // Checking time since last recorded
        Current = std::chrono::steady_clock::now();
        long long Duration =
            std::chrono::duration_cast< std::chrono::milliseconds >( Current -
                                                                     Start )
                .count();
        if ( Duration < 1 ) continue;

        SuspendThread( IntProfiler->MainThread );

        // Getting info
        CONTEXT Context = { 0 };
        Context.ContextFlags = WOW64_CONTEXT_i386 | CONTEXT_CONTROL;
        GetThreadContext( IntProfiler->MainThread, &Context );

        ResumeThread( IntProfiler->MainThread );

        // Saving to list and checking if max samples have been gotten
        IntProfiler->EipList.push_back( Context );
        if ( IntProfiler->EipList.size() >= HitTotal ) {
            return;
        }

        Start = std::chrono::steady_clock::now();
    }
}

/**
 * @brief Setting up output file.
 *
 */
void Profiler::startFile() {
    // Checking if file is already open
    if ( HasWritten ) return;

    // Opening file and setting csv headers
    int err = fopen_s( &( IntProfiler->DebugFile ), "ProfileReport.csv", "w+" );
    if ( err != 0 ) {
        printf( "Failed to open file." );
        return;
    }

    fprintf( IntProfiler->DebugFile, "Function, Hit Count, Percentage\n" );
    HasWritten = true;
}

/**
 * @brief Closes output file
 *
 */
void Profiler::closeFile() {
    errno_t err = fclose( IntProfiler->DebugFile );
    if ( err != 0 ) printf( "Failed to close file." );
}

} // namespace SquirrelEngine
