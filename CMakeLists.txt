cmake_minimum_required(VERSION 3.10)

# Everyone says not to do this...
set(CMAKE_C_COMPILER "clang")

project(psed LANGUAGES C)

# https://en.wikipedia.org/wiki/C_(programming_language)#C11
# global C_STANDARD = 11;
set_property(GLOBAL PROPERTY C_STANDARD 11)

# For clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# If macPorts is installed...
if (EXISTS /opt/local/include)
  include_directories(AFTER /opt/local/include)
  link_directories(/opt/local/lib)
endif()

# would default to STATIC, but we are explicit
add_library(libpsed STATIC lib/src/psed.c lib/src/program.c lib/psed.h)
target_compile_options(libpsed PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
# clang specific
target_compile_options(libpsed PRIVATE -Wmissing-noreturn)

# link pcre2
add_subdirectory(../../third_party/pcre2 ${CMAKE_CURRENT_BINARY_DIR}/pcre2)
target_link_libraries(libpsed PRIVATE pcre2-8-static)

add_executable(psed lib/main.c lib/psed.h)
target_link_libraries(psed libpsed)

# test suite
add_executable(test_entrypoint tests/foo.c lib/psed.h tests/test.h)
target_link_libraries(test_entrypoint libpsed)

# libcheck
add_subdirectory(../../third_party/libcheck ${CMAKE_CURRENT_BINARY_DIR}/libcheck)
target_link_libraries(test_entrypoint check)

# custom targets do not provide outputs, and are thus always outdated
add_custom_target(
  test # target name
  test_entrypoint # COMMAND
  COMMENT "Executing test suite..." # actually prints message
)
