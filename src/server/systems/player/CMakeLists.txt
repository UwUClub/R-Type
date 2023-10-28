target_sources(server PRIVATE
        System+WelcomePlayer.cpp
        System+MovePlayer.cpp
        System+PlayerShoot.cpp
        System+PlayerHit.cpp
        System+KillPlayer.cpp
        System+DisconnectPlayer.cpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
