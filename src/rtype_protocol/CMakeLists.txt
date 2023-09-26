set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(rtype_protocol STATIC
        ServerGameEvent.hpp
        ServerGameEvent.cpp
        ClientGameEvent.hpp
        ClientGameEvent.cpp
        Packets.hpp
)

target_link_libraries(rtype_protocol
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        ecs
)

target_include_directories(rtype_protocol PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../ecs"
        "${CMAKE_CURRENT_SOURCE_DIR}/../ecs/Event"
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(rtype_protocol PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
