find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(flappy_bird PRIVATE
        System+ApplyGravity.cpp
        System+Jump.cpp
)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(flappy_bird PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
