cmake_minimum_required(VERSION 3.10)

# Everyone says not to do this...
set(CMAKE_C_COMPILER "clang")

project(sed_pcre LANGUAGES C)

# https://en.wikipedia.org/wiki/C_(programming_language)#C11
# global C_STANDARD = 11;
set_property(GLOBAL PROPERTY C_STANDARD 11)

add_executable(sed_pcre_entrypoint lib/main.c)

# would default to STATIC, but we are explicit
add_library(sed_pcre_library STATIC lib/src/sed-pcre.c)
target_compile_options(sed_pcre_library PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
# clang specific
target_compile_options(sed_pcre_library PRIVATE -Wmissing-noreturn)

target_link_libraries(sed_pcre_entrypoint sed_pcre_library)

add_executable(test_entrypoint tests/foo.c)
target_link_libraries(test_entrypoint sed_pcre_library)

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
