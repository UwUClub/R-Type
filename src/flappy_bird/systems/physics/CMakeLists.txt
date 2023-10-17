target_sources(flappy_bird PRIVATE
        System+ApplyGravity.cpp
        System+Jump.cpp
)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
