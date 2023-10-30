target_sources(client PRIVATE
        System+MoveBonus.cpp
        System+TriggerBonus.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
