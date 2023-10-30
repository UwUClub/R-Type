target_sources(client PRIVATE
        System+CreateMusic.cpp
        System+PlayMusic.cpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
