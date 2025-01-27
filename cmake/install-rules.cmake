install(
    TARGETS raylib-demo_exe
    RUNTIME COMPONENT raylib-demo_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
