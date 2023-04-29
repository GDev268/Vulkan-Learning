cmake_minimum_required(VERSION 3.14)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/makeFind")

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")

project(HelloVulkanTriangle, VERSION 0.1.0)

include_directories("include/")

file(GLOB_RECURSE SPEACKER_SOURCE CONFIGURE_DEPENDS "source/*.cpp")

find_package(OpenGL REQUIRED)

find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(${VULKAN_INCLUDE_DIRS})

add_executable(HelloVulkanTriangle ${SPEACKER_SOURCE})

