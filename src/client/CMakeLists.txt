find_package(Boost REQUIRED COMPONENTS system thread)
find_package(SDL2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE main.cpp)

add_subdirectory(network)

target_link_libraries(client
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ecs
        ${SDL2_LIBRARIES}
        ${Boost_LIBRARIES}
        ecs
        rtype_protocol
)

target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/network")
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(client PRIVATE ${SDL2_INCLUDE_DIRS})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
