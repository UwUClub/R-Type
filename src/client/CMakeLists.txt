find_package(Threads REQUIRED)

target_sources(client PRIVATE
        main.cpp
        SFMLDisplayClass.cpp
)

add_subdirectory(network)
add_subdirectory(systems)

    target_link_libraries(client
            PRIVATE R_Type::R_Type_options
            R_Type::R_Type_warnings
            sfml-graphics
            sfml-window
            sfml-system
            ${Boost_LIBRARIES}
            Boost::serialization
            Threads::Threads
            ecs
            rtype
            Boost::asio
            Boost::uuid
    )

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
