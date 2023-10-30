set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(rtype PRIVATE
        TypeUtils.cpp
)

add_subdirectory(events)
add_subdirectory(components)

target_link_libraries(rtype
        PRIVATE
        R_Type::R_Type_warnings
        ecs
)

target_include_directories(rtype PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(rtype PRIVATE "${PROJECT_SOURCE_DIR}/extern/EwECS/includes")

set_target_properties(rtype PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
