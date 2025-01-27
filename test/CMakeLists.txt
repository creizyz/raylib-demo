# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(raylib-demoTests LANGUAGES CXX)

# ---- Tests ----

add_executable(raylib-demo_test source/raylib-demo_test.cpp)
target_link_libraries(raylib-demo_test PRIVATE raylib-demo_lib)
target_compile_features(raylib-demo_test PRIVATE cxx_std_20)

add_test(NAME raylib-demo_test COMMAND raylib-demo_test)

# ---- End-of-file commands ----

add_folders(Test)
