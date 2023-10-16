cmake_minimum_required(VERSION 3.15)

target_include_directories(
    client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(Geometry)
add_subdirectory(Graphics)
add_subdirectory(Events)
