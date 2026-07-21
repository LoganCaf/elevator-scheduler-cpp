cmake_minimum_required(VERSION 3.20)
project(ElevatorScheduler VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(elevator_core src/elevator.cpp)
target_include_directories(elevator_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(elevator src/main.cpp)
target_link_libraries(elevator PRIVATE elevator_core)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(elevator_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.0
  )
  FetchContent_MakeAvailable(Catch2)

  add_executable(
    elevator_tests
    tests/elevatorTestsAddTarget.cpp
    tests/elevatorTestsInit.cpp
    tests/elevatorTestsMove.cpp
    tests/elevatorTestsVisitAll.cpp
    tests/elevatorTestsVisitAllNearest.cpp
  )
  target_link_libraries(elevator_tests PRIVATE elevator_core Catch2::Catch2WithMain)

  include(Catch)
  catch_discover_tests(elevator_tests)
endif()
