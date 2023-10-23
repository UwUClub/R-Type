add_subdirectory(player)
add_subdirectory(bot)
add_subdirectory(enemy)
add_subdirectory(missile)
add_subdirectory(bonus)
add_subdirectory(background)
add_subdirectory(graphic)

target_sources(client PRIVATE
        System.hpp
        AddEntity.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
