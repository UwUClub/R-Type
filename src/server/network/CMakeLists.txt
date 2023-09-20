find_package(Boost REQUIRED COMPONENTS system thread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/NetworkHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/NetworkHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/SingleRequestListener.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/SingleRequestListener.cpp"
)

target_link_libraries(server
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
)

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
