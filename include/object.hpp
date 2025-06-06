/**
 *
 * @file object.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Declares the Object base class, which provides type information and
 * base functionality for all objects in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP
#pragma once

#include <string>

namespace SquirrelEngine {

/**
 * @brief Base class for all objects in SquirrelEngine.
 */
class Object {
public:
    /**
     * @brief Default constructor for Object.
     */
    Object() : m_type( 0 ) {}

    /**
     * @brief Virtual destructor for Object.
     */
    virtual ~Object() = default;

    /**
     * @brief Structure representing type information for an object.
     */
    struct Type {
        /**
         * @brief Constructs a Type with a given type ID.
         * @param t_typeId The type ID.
         */
        Type( const uint32_t t_typeId ) : typeId( t_typeId ) {}

        std::string typeName; //!< Name of the type.
        uint32_t typeId;      //!< Unique type identifier.
    };

protected:
    Type m_type; //!< Type information for the object.
};

} // namespace SquirrelEngine

#endif
