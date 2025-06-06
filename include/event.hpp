/**
 *
 * @file event.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Defines the base Event class for the SquirrelEngine event system.
 * @date 2025-06-06
 *
 */

#ifndef EVENT_HPP
#define EVENT_HPP
#pragma once

#include "object.hpp"

namespace SquirrelEngine {

class Event : public Object {
public:
    /**
     * @brief Default constructor for Event.
     */
    Event() = default;

    /**
     * @brief Virtual destructor for Event.
     */
    virtual ~Event() = default;
};

} // namespace SquirrelEngine

#endif
