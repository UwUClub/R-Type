target_sources(flappybird PRIVATE
        System+DisplayEntities.cpp
        System+GetInput.cpp
        System+LoadTextures.cpp
        System+SDLQuit.cpp
        System+MoveBackground.cpp
)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
