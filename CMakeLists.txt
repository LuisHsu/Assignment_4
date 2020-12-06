cmake_minimum_required(VERSION 3.12)
project(Assignment_4)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vulkan
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include)

# Wayland
find_package(Wayland REQUIRED)
include_directories(${Wayland_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(spining_cube
    main.cpp
    lib/SpiningCube.cpp
    lib/Window.cpp
)
target_link_libraries(spining_cube
    ${Vulkan_LIBRARIES}
    ${Wayland_LIBRARIES}
)