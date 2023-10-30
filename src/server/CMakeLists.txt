set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        main.cpp
        )

add_subdirectory(network)
add_subdirectory(systems)
add_subdirectory(timers)

target_link_libraries(server
        PRIVATE
        R_Type::R_Type_warnings
        ecs
        rtype
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE "${PROJECT_SOURCE_DIR}/extern/EwECS/includes")

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
