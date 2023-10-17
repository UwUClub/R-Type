target_sources(client PRIVATE
        System+CreateBackground.cpp
        System+MoveBackground.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
