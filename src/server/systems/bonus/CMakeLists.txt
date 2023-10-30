target_sources(server PRIVATE
        System+MoveBonus.cpp
        System+TriggerBonus.cpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
