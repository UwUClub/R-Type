include(../../cmake/FindSDL2.cmake)

find_package(Boost REQUIRED COMPONENTS system thread serialization)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        main.cpp
        System.cpp
        SDLDisplayClass.cpp
)

add_subdirectory(network)

if (SDL2_DOWNLOADED)
    target_link_libraries(client
            PRIVATE R_Type::R_Type_options
            R_Type::R_Type_warnings
            SDL2::SDL2main
            SDL2::SDL2-static
            SDL2_image::SDL2_image-static
            ${Boost_LIBRARIES}
            Boost::serialization
            Threads::Threads
            ecs
            rtype_protocol
            Boost::asio
            Boost::serialization
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
            rtype_protocol
            Boost::asio
            Boost::serialization
    )
endif()


target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})

if (SDL2_DOWNLOADED)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
