set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

find_package(Boost REQUIRED COMPONENTS system thread serialization uuid asio)
find_package(SDL2 REQUIRED)

target_sources(rtype PRIVATE
        Packets.hpp
        Values.hpp
        NetworkHandler.hpp
        NetworkHandler.cpp
        TypeUtils.hpp
        TypeUtils.cpp
)

add_subdirectory(events)
add_subdirectory(components)

target_link_libraries(rtype
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
        Boost::asio
        Boost::serialization
        Boost::uuid
        ecs
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image
)

target_include_directories(rtype PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)

target_include_directories(client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)

set_target_properties(rtype PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
