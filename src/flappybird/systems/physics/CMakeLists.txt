target_sources(flappybird PRIVATE
        System+ApplyGravity.cpp
        System+Jump.cpp
)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
