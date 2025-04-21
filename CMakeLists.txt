cmake_minimum_required(VERSION 3.5.0)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME ProjectName)
project(${ProjectName} VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

#
# GLFW options
#
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /std:c++latest")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++20")

    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

#
# Libraries with CMake
#
add_subdirectory(libraries/fmt)
add_subdirectory(libraries/glfw)

#
# Source files
#
file(GLOB_RECURSE LIBRARY_SOURCES
    libraries/glad/src/glad.c
    libraries/imgui/*.cpp
)
file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    src/*.cxx
    src/*.cc
    src/*.c
    src/utils/*.cpp
)

file(COPY assets/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
file(COPY assets/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

file(COPY assets/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${LIBRARY_SOURCES})

include_directories(
    include/
    SYSTEM libraries/fmt/include
    SYSTEM libraries/glad/include
    SYSTEM libraries/glfw/include
    SYSTEM libraries/glm/include
    SYSTEM libraries/glm
    SYSTEM libraries/imgui
)

target_link_libraries(${PROJECT_NAME}
    fmt::fmt
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
)
