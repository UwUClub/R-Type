find_package(Boost REQUIRED COMPONENTS system thread serialization uuid)
find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        main.cpp
        SDLDisplayClass.cpp
)

add_subdirectory(network)
add_subdirectory(systems)

if (SDL2_DOWNLOADED)
    target_link_libraries(client
            PRIVATE R_Type::R_Type_options
            R_Type::R_Type_warnings
            SDL2::SDL2main
            SDL2::SDL2
            SDL2_image
            ${Boost_LIBRARIES}
            Boost::serialization
            Threads::Threads
            ecs
            rtype
            Boost::asio
            Boost::uuid
    )
else()
    target_link_libraries(client
            PRIVATE R_Type::R_Type_options
            R_Type::R_Type_warnings
            SDL2::SDL2main
            SDL2::SDL2
            SDL2_image
            ${Boost_LIBRARIES}
            Boost::serialization
            Threads::Threads
            ecs
            rtype
            Boost::asio
            Boost::serialization
            Boost::uuid
    )
endif()

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(client PRIVATE "../../build/_deps/sdl2-src/include/SDL2")
target_include_directories(client PRIVATE "../../build/_deps/sdl2_image-src/include")

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
