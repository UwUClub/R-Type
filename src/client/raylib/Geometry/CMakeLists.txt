cmake_minimum_required(VERSION 3.15)

target_include_directories(
    client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    client
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Geometry.cpp
)
