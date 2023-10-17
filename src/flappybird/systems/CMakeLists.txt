add_subdirectory(graphic)
add_subdirectory(physics)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
