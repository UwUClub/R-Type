target_sources(server PRIVATE
        System+SpawnEnemy.cpp
        System+MoveEnemy.cpp
        System+EnemyShoot.cpp
        System+EnemyHit.cpp
        System+KillEnemy.cpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
