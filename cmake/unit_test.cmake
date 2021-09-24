# Create the unit testing executable.
# By using glob, any test source files that are added to test/ will automatically
# be added to the unit testing executable.
file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(unit_test ${SOURCE_FILES_NO_MAIN} ${TEST_SOURCE_FILES})
# Enable CMake `make test` support.
enable_testing()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  target_compile_options(unit_test PRIVATE -Wall -Wextra -Werror -fconcepts -g -O1 -fsanitize=address -fno-omit-frame-pointer)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  target_compile_options(unit_test PRIVATE -Wall -Wextra -Werror -fconcepts -g -O0 -fprofile-arcs -ftest-coverage)
  target_link_libraries(unit_test PRIVATE "-lgcov --coverage")
  execute_process(COMMAND
          ${CMAKE_CXX_COMPILER} -dumpversion
          OUTPUT_VARIABLE GCC_VERSION)
  string(STRIP ${GCC_VERSION} GCC_VERSION)
  MESSAGE(STATUS "gcc version: [" ${GCC_VERSION} "]")
  set(GCOV_TOOL "gcov-11")

  add_custom_target("coverage"
          COMMAND "lcov" --directory . --zerocounters
          COMMAND ctest
          COMMAND "lcov" --directory . --capture --output-file coverage.info --gcov-tool ${GCOV_TOOL}
          COMMAND "lcov" --remove coverage.info "'/t/*'" "'/boost_1_63_0/*'" "'/usr/*'" --output-file coverage.info.cleaned
          COMMAND "rm" coverage.info
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          )
  add_custom_target("coverage-report"
          COMMAND "genhtml" -o coverage coverage.info.cleaned
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          DEPENDS "coverage"
          )
endif()

add_test(NAME UnitTests COMMAND unit_test)
