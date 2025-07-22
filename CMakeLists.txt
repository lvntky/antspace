# CMakeLists.txt for Antspace Project
cmake_minimum_required(VERSION 3.16)

project(Antspace 
    VERSION 0.1.0 
    DESCRIPTION "SDL2-based application"
    LANGUAGES CXX
)

# =============================================================================
# Project Configuration
# =============================================================================

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Options
option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

# =============================================================================
# Dependencies
# =============================================================================

# Find SDL2 using multiple methods for better compatibility
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    if(NOT SDL2_FOUND)
        message(FATAL_ERROR "SDL2 not found! Please install SDL2 development libraries.")
    endif()
endif()

# =============================================================================
# Source Files
# =============================================================================

set(SOURCES
    src/main.cpp
    src/Ant.cpp
    # Add additional source files here
)

set(HEADERS
    # Add header files here if needed for IDE integration
)

# =============================================================================
# Target Definition
# =============================================================================

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# =============================================================================
# Include Directories
# =============================================================================

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# SDL2 include directories
if(TARGET SDL2::SDL2)
    # Modern CMake SDL2 target
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
else()
    # Fallback for older SDL2 installations
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
    target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_CFLAGS_OTHER})
endif()

# =============================================================================
# Compiler Flags
# =============================================================================

# Common flags for all compilers
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# MSVC-specific flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4                     # High warning level
        /permissive-           # Standards conformance
        /Zc:__cplusplus        # Use correct __cplusplus macro
        /utf-8                 # Use UTF-8 encoding
    )
    
    if(ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(${PROJECT_NAME} PRIVATE /WX)
    endif()
    
    # Release-specific flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/O2>     # Optimize for speed
        $<$<CONFIG:Release>:/DNDEBUG>
    )
    
    # Debug-specific flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/Od>       # No optimization
        $<$<CONFIG:Debug>:/Zi>       # Debug information
        $<$<CONFIG:Debug>:/RTC1>     # Runtime checks
    )

# GCC/Clang flags
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall                  # All common warnings
        -Wextra               # Extra warnings
        -Wpedantic            # Enforce strict ISO compliance
        -Wcast-align          # Warn about pointer casts with increased alignment
        -Wcast-qual           # Warn about casts that remove qualifiers
        -Wctor-dtor-privacy   # Warn about class constructors and destructors privacy
        -Wdisabled-optimization # Warn when optimization is disabled
        -Wformat=2            # Extra format string checks
        -Winit-self           # Warn about uninitialized variables
        -Wmissing-declarations # Warn about missing declarations
        -Wmissing-include-dirs # Warn about missing include directories
        -Wold-style-cast      # Warn about C-style casts
        -Woverloaded-virtual  # Warn about overloaded virtual functions
        -Wredundant-decls     # Warn about redundant declarations
        -Wshadow              # Warn about variable shadowing
        -Wsign-conversion     # Warn about sign conversions
        -Wsign-promo          # Warn about promotions from signed to unsigned
        -Wstrict-overflow=5   # Warn about strict overflow
        -Wswitch-default      # Warn about switch statements without default
        -Wundef               # Warn about undefined macros
        -fno-common           # Detect duplicate symbols
        -pipe                 # Use pipes rather than temp files
    )
    
    if(ENABLE_WARNINGS_AS_ERRORS)
        target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
    endif()
    
    # Release-specific flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:-O3>           # Aggressive optimization
        $<$<CONFIG:Release>:-march=native> # Optimize for current CPU
        $<$<CONFIG:Release>:-DNDEBUG>
    )
    
    # Debug-specific flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-O0>                    # No optimization
        $<$<CONFIG:Debug>:-g3>                    # Debug information
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer> # Better debugging info
    )
    
    # Sanitizers (Debug only)
    if(ENABLE_SANITIZERS)
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address>
            $<$<CONFIG:Debug>:-fsanitize=undefined>
            $<$<CONFIG:Debug>:-fsanitize=leak>
        )
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address>
            $<$<CONFIG:Debug>:-fsanitize=undefined>
            $<$<CONFIG:Debug>:-fsanitize=leak>
        )
    endif()
endif()

# =============================================================================
# Installation (Optional)
# =============================================================================

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# =============================================================================
# Debug Information
# =============================================================================

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Sanitizers enabled: ${ENABLE_SANITIZERS}")
message(STATUS "Warnings as errors: ${ENABLE_WARNINGS_AS_ERRORS}")

if(SDL2_FOUND)
    if(TARGET SDL2::SDL2)
        message(STATUS "SDL2 found: Using modern CMake target")
    else()
        message(STATUS "SDL2 found: Using legacy variables")
        message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
        message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
    endif()
endif()
