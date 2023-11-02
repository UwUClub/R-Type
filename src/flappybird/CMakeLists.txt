set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(flappybird PRIVATE
        main.cpp
)

add_subdirectory(components)
add_subdirectory(systems)

target_link_libraries(flappybird PRIVATE
        ecs
)

target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components)
target_include_directories(flappybird PRIVATE "${PROJECT_SOURCE_DIR}/extern/EwECS/includes")

set_target_properties(flappybird PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
