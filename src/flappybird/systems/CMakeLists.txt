add_subdirectory(physics)
add_subdirectory(ground)
add_subdirectory(score)
add_subdirectory(pipe)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
