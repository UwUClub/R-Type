target_sources(client PRIVATE
        System+CreateEnemy.cpp
        System+MoveEnemy.cpp
        System+TriggerEnemyShoot.cpp
        System+EnemyHit.cpp
        System+TriggerEnemyDeath.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
