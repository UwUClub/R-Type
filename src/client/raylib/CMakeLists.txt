cmake_minimum_required(VERSION 3.15)

target_include_directories(
    client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME_CLIENT}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/UnloadRaylib.cpp
)

add_subdirectory(Geometry)
add_subdirectory(Graphics)
add_subdirectory(Audio)
add_subdirectory(Events)
