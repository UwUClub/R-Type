cmake_minimum_required(VERSION 3.15...3.23)

target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ResourcesManager.hpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
