/**
 *
 * @file core.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Sink header file for engine
 * @date 2025-04-20
 *
 */

#ifndef CORE_HPP
#define CORE_HPP
#pragma once

// From libraries
#include <fmt/core.h>

// From source
#include "cameraComponent.hpp"
//// Engine
#include "engine.hpp"
#include "system.hpp"
#include "world.hpp"

#include "entity.hpp"
#include "eventSystem.hpp"

//// Input
#include "inputSystem.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

//// Graphics
#include "mesh.hpp"
#include "model.hpp"
#include "objectRenderer.hpp"
#include "shader.hpp"
#include "window.hpp"

//// Utilities
#include "editor.hpp"
#include "error_codes.hpp"
#include "utils/trace.hpp"
#include "utils/time_manager.hpp"

//// Editor windows
#include "editor_windows/world_editor.hpp"

#endif
