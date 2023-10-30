add_subdirectory(bird)
add_subdirectory(environment)
add_subdirectory(score)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
