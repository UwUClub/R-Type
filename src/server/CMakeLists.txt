find_package(Boost REQUIRED COMPONENTS system thread serialization)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        main.cpp
        )

add_subdirectory(network)
add_subdirectory(systems)

target_link_libraries(server
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image
        ${Boost_LIBRARIES}
        Boost::asio
        Boost::serialization
        ecs
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
