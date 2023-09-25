cmake_minimum_required(VERSION 3.15...3.23)

find_package(Boost REQUIRED COMPONENTS system)

target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ResourcesManager.hpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE ${Boost_INCLUDE_DIRS})
