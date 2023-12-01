cmake_minimum_required(VERSION 3.12)

# ---- Project ----
project(
  cpphw
  VERSION 1.0
  LANGUAGES C CXX)

# ---- Env var for SonarLint ----
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- C++ standard ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Function to create executables from source files in a directory ----
function(create_executables DIRECTORY)
  file(GLOB_RECURSE SRC_FILES "${DIRECTORY}/*.cpp")

  foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(EXE_NAME ${SRC_FILE} NAME_WE)
    add_executable(${DIRECTORY}${EXE_NAME} ${SRC_FILE})
    set_target_properties(${DIRECTORY}${EXE_NAME} PROPERTIES CXX_STANDARD 20)
  endforeach()
endfunction()

# ---- Create executables for subdirectories ----
set(SUBDIRECTORIES loops functions arrays)

foreach(SUBDIR ${SUBDIRECTORIES})
  create_executables(${SUBDIR})
endforeach()

# ---- Add googletest ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Enable testing ----
enable_testing()

# ---- Special case for 'date' directory ----
add_executable(date date/date.cpp date/tests.cpp)
target_include_directories(date PRIVATE date)
target_link_libraries(date PRIVATE GTest::gtest_main)
set_target_properties(date PROPERTIES CXX_STANDARD 20)
include(GoogleTest)
gtest_discover_tests(date)
