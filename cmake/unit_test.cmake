# Create the unit testing executable.
# By using glob, any test source files that are added to test/ will automatically
# be added to the unit testing executable.
file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(unit_test ${SOURCE_FILES_NO_MAIN} ${TEST_SOURCE_FILES})
# Enable CMake `make test` support.
enable_testing()
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -fconcepts -fimplicit-modules -fimplicit-module-maps -c helloworld.cpp -Xclang -emit-module-interface -o tsfile.pcm)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  target_compile_options(tsfile PRIVATE -Wall -Wextra -Werror -fconcepts -fmodules-ts)

endif()

add_test(NAME UnitTests COMMAND unit_test)
