add_subdirectory(physics)
add_subdirectory(ground)
add_subdirectory(score)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
