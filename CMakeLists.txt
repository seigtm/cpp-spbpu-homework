cmake_minimum_required(VERSION 3.12)

# ---- Project ----
project(
  cpphw
  VERSION 1.0
  LANGUAGES CXX)

# ---- Env var for SonarLint ----
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# ---- Special case for 'classes' directory ----
add_executable(classes classes/main.cpp)
target_include_directories(classes PRIVATE classes)
set_target_properties(classes PROPERTIES CXX_STANDARD 20)
