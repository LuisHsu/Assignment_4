cmake_minimum_required(VERSION 3.14)
project(Assignment_4)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies$
find_package(Vulkan REQUIRED)
find_package(Wayland REQUIRED)
find_package(Libinput REQUIRED)
find_package(udev REQUIRED)
find_package(Systemd REQUIRED)
include_directories(
    ${Vulkan_INCLUDE_DIRS}
    ${Wayland_INCLUDE_DIRS}
    ${Libinput_INCLUDE_DIRS}
    ${UDEV_INCLUDE_DIRS}
    ${SYSTEMD_INCLUDE_DIRS}
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
add_executable(spining_cube
    src/main.cpp
    src/SpiningCube.cpp
    src/Window.cpp
    src/Input.cpp
    src/EventHandler.cpp
    src/Timer.cpp
)
target_link_libraries(spining_cube
    ${Vulkan_LIBRARIES}
    ${Wayland_LIBRARIES}
    ${Libinput_LIBRARIES}
    ${UDEV_LIBRARIES}
    ${SYSTEMD_LIBRARIES}
)