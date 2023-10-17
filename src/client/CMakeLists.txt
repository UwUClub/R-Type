find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        main.cpp
        SFMLDisplayClass.cpp
)

add_subdirectory(network)
add_subdirectory(systems)

target_link_libraries(client
            PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
            Threads::Threads
            ecs
            rtype
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

