# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(GumShoe)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find SDL3 package
find_package(SDL3 REQUIRED)

# Add your executable
add_executable(${PROJECT_NAME} main.cpp)

# Link SDL3 to your project
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Include SDL3 headers (optional, just in case)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})

# Set the required flags for the linker if necessary
if(APPLE)
    # For macOS, you might need additional flags for linking
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework SDL3")
elseif(WIN32)
    # For Windows, ensure SDL3 is properly linked
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
elseif(UNIX)
    # For Linux, the usual package should work
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif()

