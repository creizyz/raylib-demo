#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "raylib-demo" ? 0 : 1;
}
