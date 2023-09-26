find_package(Boost REQUIRED COMPONENTS system thread asio serialization)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerNetworkHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerNetworkHandler.cpp"
)

target_link_libraries(server
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
        ecs
        rtype_protocol
        Boost::asio
        Threads::Threads
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/../../ecs"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../rtype_protocol"
        ${Boost_INCLUDE_DIRS}
)

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
