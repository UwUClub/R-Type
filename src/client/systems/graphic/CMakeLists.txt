target_sources(client PRIVATE
        System+DisplayEntities.cpp
        System+GetInput.cpp
        System+LoadTextures.cpp
        System+CreateServerFullErrorMessage.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
