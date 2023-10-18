target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowEvent.cpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
