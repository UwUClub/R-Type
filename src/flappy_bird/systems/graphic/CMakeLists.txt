target_sources(flappy_bird PRIVATE
        System+DisplayEntities.cpp
        System+GetInput.cpp
        System+LoadTextures.cpp
        System+SDLQuit.cpp
)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
