cmake_minimum_required(VERSION 3.10)

# Everyone says not to do this...
set(CMAKE_C_COMPILER "clang")

project(psed LANGUAGES C)

# https://en.wikipedia.org/wiki/C_(programming_language)#C11
# global C_STANDARD = 11;
set_property(GLOBAL PROPERTY C_STANDARD 11)

# If macPorts is installed...
if (EXISTS /opt/local/include)
  include_directories(AFTER /opt/local/include)
  link_directories(/opt/local/lib)
endif()

add_executable(psed_entrypoint lib/main.c lib/psed.h)

# would default to STATIC, but we are explicit
add_library(libpsed STATIC lib/src/psed.c lib/src/program.c lib/psed.h)
target_compile_options(libpsed PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
# clang specific
target_compile_options(libpsed PRIVATE -Wmissing-noreturn)

target_link_libraries(psed_entrypoint libpsed)

add_executable(test_entrypoint tests/foo.c lib/psed.h)
target_link_libraries(test_entrypoint libpsed)

# custom targets do not provide outputs, and are thus always outdated
add_custom_target(
  test
  test_entrypoint # COMMAND
  COMMENT "Executing test suite..." # actually prints message
)

# This requires check to have been installed as a system library
target_link_libraries(test_entrypoint check)

if (APPLE)
  message(STATUS "Building for macOS...")
# TODO Use the LINUX var once we update to cmake 3.25
# https://cmake.org/cmake/help/latest/variable/LINUX.html
elseif (UNIX)
  message(STATUS "Building for linux...")
  target_link_libraries(test_entrypoint m) # math
  # https://refspecs.linuxfoundation.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/app-librt.html
  target_link_libraries(test_entrypoint rt) # realtime extensions
  target_link_libraries(test_entrypoint pthread)
  target_link_libraries(test_entrypoint subunit)
else()
  message(FATAL_ERROR "Unsupported platform!")
endif()
