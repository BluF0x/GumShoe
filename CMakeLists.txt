cmake_minimum_required(VERSION 3.16)

# Set project name
project(GumShoe VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3 package
if (WIN32)
	set(CMAKE_PREFIX_PATH "C:/SDL" ${CMAKE_PREFIX_PATH})
endif()
find_package(SDL3 REQUIRED)

# Automatically add all .cpp and .h files from include/
file(GLOB_RECURSE PROJECT_SOURCES "include/*.cpp" "include/*.h")

# Add your main source file manually
set(MAIN_SOURCE "src/main.cpp")

# Add your executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${PROJECT_SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link SDL3 to your project
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# Include SDL3 headers (optional)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL3_INCLUDE_DIRS})

# Platform-specific linker flags
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework OpenGL" "-framework SDL3")
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif()
