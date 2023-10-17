add_subdirectory(graphic)
add_subdirectory(physics)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
