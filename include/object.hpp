
#ifndef OBJECT_HPP
#define OBJECT_HPP
#pragma once

#include <string>

namespace SquirrelEngine {

class Object {
public:
    Object() : m_type( 0 ) {}
    virtual ~Object() = default;

    struct Type {
        Type( const uint32_t t_typeId ) : typeId( t_typeId ) {}

        std::string typeName;
        uint32_t typeId;
    };

protected:
    Type m_type;
};

} // namespace SquirrelEnigine

#endif
