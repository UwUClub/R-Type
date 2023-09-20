find_package(Boost REQUIRED COMPONENTS system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(client PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientNetworkHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientNetworkHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Packets.hpp"
)

target_link_libraries(client
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
)

target_include_directories(client
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../game_common"
)

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
