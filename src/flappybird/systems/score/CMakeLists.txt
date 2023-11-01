target_sources(flappybird PRIVATE
        System+UpdateScore.cpp
)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
