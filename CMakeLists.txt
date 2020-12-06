cmake_minimum_required(VERSION 3.12)
project(Assignment_4)

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(spining_cube
    main.cpp
)
target_link_libraries(spining_cube
    ${Vulkan_LIBRARIES}
)