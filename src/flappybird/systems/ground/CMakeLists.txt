target_sources(flappybird PRIVATE
        System+MoveGround.cpp
        System+KillBird.cpp
)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
