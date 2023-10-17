target_sources(client PRIVATE
        System+MovePlayer.cpp
        System+TriggerPlayerShoot.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
