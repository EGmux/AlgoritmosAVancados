﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#    
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

option(ENABLE_TESTS "Enable gtest testing"  ON)

project ("AlgoritmosAVancados")

# Include sub-projects.
add_subdirectory ("AlgoritmosAVancados")

# Include headers
add_library(PLACEHOLDERlib STATIC "include/includePLACEHOLDER.hpp" "src/srcPLACEHOLDER.cpp")
target_include_directories(PLACEHOLDERlib PUBLIC "include")
target_compile_features(PLACEHOLDERlib PUBLIC cxx_std_17)

IF(ENABLE_TESTS)
	enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(PLACEHOLDERTests "tests/testsPLACEHOLDER.cpp")
target_link_libraries(PLACEHOLDERTests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(PLACEHOLDERTests)
endif()

## Main application
add_executable(main "apps/mainPLACEHOLDER.cpp")
target_link_libraries(main PUBLIC PLACEHOLDERlib)


