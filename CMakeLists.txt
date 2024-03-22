# cmake -S . -B build
# cmake --build build

include(CMakePrintHelpers)

option(BUILD_CODEGRADE_TESTS "Build test suites into separate executables" OFF)

cmake_minimum_required(VERSION 3.10)
project(hw3 LANGUAGES C CXX)
find_package(GTest REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)


# Build standalone test case suites for CodeGrade. These are separate executables so that CodeGrade can run them individually.
file(GLOB SOURCES tests/src/tests_*.cpp)
file(GLOB TEST_CASE_FILES tests/src/tests_print_board_sf*.cpp)

# Extract the test suite names from the file paths
set(TEST_SUITES "multiple_turns_asan" "multiple_turns_valgrind" "multiple_turns" 
  "place_tiles_invalid_asan" "place_tiles_invalid_valgrind" "place_tiles_invalid"
  "place_tiles_valid_asan" "place_tiles_valid_valgrind" "place_tiles_valid"
  "undo_place_tiles_asan" "undo_place_tiles_valgrind" "undo_place_tiles")
foreach(TEST_CASE_FILE ${TEST_CASE_FILES})
  get_filename_component(TEST_SUITE_NAME ${TEST_CASE_FILE} NAME_WE)
  list(APPEND TEST_SUITES ${TEST_SUITE_NAME})
endforeach()

if (BUILD_CODEGRADE_TESTS)
  foreach(TEST_SUITE IN LISTS TEST_SUITES)
    add_executable(tests_${TEST_SUITE} tests/src/tests_${TEST_SUITE}.cpp tests/src/tests_aux.cpp src/hw3.c)
    target_compile_options(tests_${TEST_SUITE} PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
    target_include_directories(tests_${TEST_SUITE} PUBLIC include tests/include)
    target_link_libraries(tests_${TEST_SUITE} PUBLIC gtest gtest_main pthread m)
  endforeach()
else()
  # Build main executable
  add_executable(hw3_main src/hw3_main.c src/hw3.c)
  target_compile_options(hw3_main PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_libraries(hw3_main PUBLIC m)
  target_include_directories(hw3_main PUBLIC include)

  # Build a single executable with all the tests. Used during development only, not on CodeGrade.
  add_executable(run_all_tests ${SOURCES} src/hw3.c)
  target_compile_options(run_all_tests PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_include_directories(run_all_tests PUBLIC include tests/include)
  target_link_libraries(run_all_tests PUBLIC gtest gtest_main pthread m)
endif()

# Build standalone executables to test functions through Valgrind.
file(GLOB SOURCES tests/src/standalone_scripts/*.c)
foreach(FILE IN LISTS SOURCES)
  get_filename_component(MyExeTarget ${FILE} NAME_WE)
  add_executable(${MyExeTarget}_valgrind ${FILE} src/hw3.c)
  target_compile_options(${MyExeTarget}_valgrind PUBLIC -g -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_libraries(${MyExeTarget}_valgrind PUBLIC m)
  target_include_directories(${MyExeTarget}_valgrind PUBLIC include tests/include)
endforeach()

# Build standalone executables to test functions with AddressSanitizer.
file(GLOB SOURCES tests/src/standalone_scripts/*.c)
foreach(FILE IN LISTS SOURCES)
  get_filename_component(MyExeTarget ${FILE} NAME_WE)
  add_executable(${MyExeTarget}_asan ${FILE} src/hw3.c)
  target_compile_options(${MyExeTarget}_asan PUBLIC -g -fsanitize=address -fsanitize=leak -fsanitize=undefined -Wall -Wextra -Wshadow -Wpedantic -Wdouble-promotion -Wformat=2 -Wundef -Werror)
  target_link_options(${MyExeTarget}_asan PUBLIC -fsanitize=address -fsanitize=leak -fsanitize=undefined)
  target_link_libraries(${MyExeTarget}_asan PUBLIC m asan)
  target_include_directories(${MyExeTarget}_asan PUBLIC include tests/include)
endforeach()