
#ifndef EVENT_HPP
#define EVENT_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {

class Event : public Object {
public:
    Event() = default;
    virtual ~Event() = default;
};

} // namespace SquirrelEngine

#endif
