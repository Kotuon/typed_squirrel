
#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#pragma once

// std includes
#include <unordered_map>
#include <string>

#include "system.hpp"

namespace SquirrelEngine {

class ShaderManager : public System {
public:
    unsigned getShader( const std::string& VertexFile,
                        const std::string& FragmentFile );
    void detachShader();
    void destroyShader( unsigned ShaderID );

    const char* readFile( const std::string& FileName );

    const std::unordered_map< std::string, unsigned >& getShaderList() const;

private:
    std::unordered_map< std::string, unsigned > ShaderList;
    std::unordered_map< unsigned, std::string > ProgramList;
    std::unordered_map< std::string, std::string > SourceList;
};

} // namespace SquirrelEngine

#endif