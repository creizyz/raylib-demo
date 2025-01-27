install(
    TARGETS raylib-demo-game
    RUNTIME COMPONENT raylib-demo_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
