cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    raylib-demo
    VERSION 0.1.0
    DESCRIPTION "Learning raylib and game development"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Global compilation flags ----

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

# ---- Declare library ----

set(LIB_SOURCE_ROOT "${PROJECT_SOURCE_DIR}/source/core" CACHE PATH "core lib folder")
file(GLOB_RECURSE LIB_HEADERS "${LIB_SOURCE_ROOT}/*.h" "${LIB_SOURCE_ROOT}/*.hpp")
file(GLOB_RECURSE LIB_SOURCES "${LIB_SOURCE_ROOT}/*.c" "${LIB_SOURCE_ROOT}/*.cpp")

add_library(
    raylib-demo-core OBJECT
        "${LIB_SOURCES}"
)

target_include_directories(
    raylib-demo-core ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${LIB_SOURCE_ROOT}>"
)

target_compile_features(raylib-demo-core PUBLIC cxx_std_20)
target_link_libraries(raylib-demo-core PUBLIC
        -lraylib
        -lm
        -ldl
        -pthread
        -lGL
)

# ---- Declare executable ----

set(EXE_SOURCE_ROOT "${PROJECT_SOURCE_DIR}/source/game" CACHE FILEPATH "game exe folder")
file(GLOB_RECURSE EXE_HEADERS "${EXE_SOURCE_ROOT}/*.h" "${EXE_SOURCE_ROOT}/*.hpp")
file(GLOB_RECURSE EXE_SOURCES "${EXE_SOURCE_ROOT}/*.c" "${EXE_SOURCE_ROOT}/*.cpp")

add_executable(raylib-demo-game "${EXE_SOURCES}")
add_executable(raylib-demo::exe ALIAS raylib-demo-game)

target_include_directories(
        raylib-demo-game ${warning_guard}
        PUBLIC
        "\$<BUILD_INTERFACE:${EXE_SOURCE_ROOT}>"
)

set_property(TARGET raylib-demo-game PROPERTY OUTPUT_NAME raylib-demo)
target_compile_features(raylib-demo-game PRIVATE cxx_std_20)
target_link_libraries(raylib-demo-game PRIVATE
        raylib-demo-core
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT raylib-demo_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of raylib-demo"
  )
endif()

include(cmake/dev-mode.cmake)
