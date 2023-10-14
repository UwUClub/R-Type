find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        main.cpp
        SDLDisplayClass.cpp
)

add_subdirectory(network)
add_subdirectory(systems)

target_link_libraries(client
    PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
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
target_include_directories(client PRIVATE "../../shared/SDL/include")
target_include_directories(client PRIVATE "../../shared/SDL_image/include")

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
