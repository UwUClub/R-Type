find_package(Boost REQUIRED COMPONENTS system thread serialization)
find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        System+DisplayEntities.cpp
        System+GetInput.cpp
        System+LoadTextures.cpp
        System+CreatePlayer.cpp
        System+MovePlayer.cpp
        System+UpdatePlayerPos.cpp
        System+SDLQuit.cpp
        System+MoveBackground.cpp
        System+SpawnEnemies.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
