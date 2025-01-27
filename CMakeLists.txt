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

# ---- Declare library ----

add_library(
    raylib-demo_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    raylib-demo_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(raylib-demo_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(raylib-demo_exe source/main.cpp)
add_executable(raylib-demo::exe ALIAS raylib-demo_exe)

set_property(TARGET raylib-demo_exe PROPERTY OUTPUT_NAME raylib-demo)

target_compile_features(raylib-demo_exe PRIVATE cxx_std_20)

target_link_libraries(raylib-demo_exe PRIVATE raylib-demo_lib)

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
