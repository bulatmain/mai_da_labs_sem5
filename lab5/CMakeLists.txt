cmake_minimum_required(VERSION 3.14)

project(lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler options
if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    add_compile_options(
        -g
        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Add interface library for headers
add_library(lab_headers INTERFACE)
target_include_directories(lab_headers INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_library(lab::headers ALIAS lab_headers)

# Add implementation library
add_library(lab_implementation
    include/suffix_tree/impl/suffix_node.cpp
    include/suffix_tree/impl/suffix_tree.cpp
)
target_link_libraries(lab_implementation PUBLIC lab::headers)
add_library(lab::implementation ALIAS lab_implementation)

# Link main executable
add_executable(lab_main src/main.cpp)
target_link_libraries(lab_main PRIVATE lab::headers lab::implementation)

# Enable testing
option(LAB_TESTING "Enable unit testing" ON)

if(LAB_TESTING)
    enable_testing()
    add_subdirectory(test)
else()
    message(STATUS "Testing is disabled")
endif()
