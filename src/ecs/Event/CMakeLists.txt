cmake_minimum_required(VERSION 3.15...3.23)

target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowEvent.cpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
