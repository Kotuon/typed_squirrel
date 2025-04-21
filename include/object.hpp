
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
        Type( const uint32_t t_classId ) : classId( t_classId ) {}

        std::string className;
        uint32_t classId;
    };

    Object::Type type();

protected:
    Type m_type;
};

} // namespace SquirrelEngine

#endif
