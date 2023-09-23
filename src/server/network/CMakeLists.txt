find_package(Boost REQUIRED COMPONENTS system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerNetworkHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerNetworkHandler.cpp"
)

target_link_libraries(server
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
