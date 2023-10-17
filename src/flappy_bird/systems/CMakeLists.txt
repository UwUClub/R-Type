find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_subdirectory(graphic)
add_subdirectory(physics)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(flappy_bird PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
