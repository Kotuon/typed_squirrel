
#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP
#pragma once

#include "component.hpp"

namespace SquirrelEngine {

class Behavior : public Component {

    class DataRecord;

public:
    Behavior( Entity* t_parent );
    ~Behavior() = default;

    void serializeComponent( DataRecord* record );

    void deserializeComponent( DataRecord* record );

private:
};

} // namespace SquirrelEngine

#endif
