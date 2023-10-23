find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        main.cpp
)

add_subdirectory(network)
add_subdirectory(systems)

target_link_libraries(client
    PRIVATE
    Threads::Threads
    ecs
    rtype
    RenderPlugin
    ${Boost_LIBRARIES}
    Boost::asio
    Boost::serialization
    Boost::serialization
    Boost::uuid
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

