cmake_minimum_required(VERSION 3.31)
project(RRR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

if (WIN32)
    set(PLATFORM_DIR windows)
elseif (APPLE)
    set(PLATFORM_DIR mac)
elseif (UNIX)
    set(PLATFORM_DIR linux)
endif()

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/${PLATFORM_DIR})

set(SHADERC_NAME    shaderc)
set(GLFW_NAME       glfw3)
set(VULKAN_NAME     vulkan-1)

find_library(SHADERC_LIB NAMES ${SHADERC_NAME}
        PATHS ${LIB_DIR}
        NO_DEFAULT_PATH
)
find_library(GLFW_LIB    NAMES ${GLFW_NAME}
        PATHS ${LIB_DIR}
        NO_DEFAULT_PATH
)
find_library(VULKAN_LIB  NAMES ${VULKAN_NAME}
        PATHS ${LIB_DIR}
        NO_DEFAULT_PATH
)

foreach(LIB SHADERC_LIB GLFW_LIB VULKAN_LIB)
    if (NOT ${LIB})
        message(FATAL_ERROR "Could not find ${LIB} in ${LIB_DIR}")
    endif()
endforeach()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${SHADERC_LIB}
        ${GLFW_LIB}
        ${VULKAN_LIB}
)
