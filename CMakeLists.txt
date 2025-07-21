cmake_minimum_required(VERSION 3.10)
project(Antspace VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found! Please install SDL2 development libraries.")
endif()

# Use target-based include directories with SYSTEM to allow <> includes
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

# Compiler warning and optimization flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4                # High warning level
        /WX                # Treat warnings as errors
        /O2                # Optimize for speed
        /permissive-       # Standards conformance
        /Zc:__cplusplus    # Use correct __cplusplus macro
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall              # All common warnings
        -Wextra            # Extra warnings
        -Wpedantic         # Enforce strict ISO compliance
        -Werror            # Treat warnings as errors
        -O3                # Optimize aggressively
        -march=native      # Optimize for current CPU architecture
        -fno-omit-frame-pointer  # Better debugging info
        -fsanitize=address,undefined # Optional: enable sanitizers (comment if not wanted)
        -fno-common        # Detect duplicate symbols
        -pipe              # Use pipes rather than temp files to speed up compile
    )
endif()

# Optionally enable sanitizers only in debug mode
option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
if(ENABLE_SANITIZERS AND NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -fsanitize=address
        -fsanitize=undefined
    )
endif()
