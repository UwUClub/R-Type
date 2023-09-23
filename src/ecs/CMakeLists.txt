set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(ecs STATIC
        World.hpp
        SparseArray.hpp
)

add_subdirectory(Event)

target_link_libraries(ecs
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
)

target_include_directories(ecs PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Event"
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
