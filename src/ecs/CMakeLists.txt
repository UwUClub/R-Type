target_sources(ecs PRIVATE
        World.hpp
        SparseArray.hpp
)

add_subdirectory(Event)

target_link_libraries(ecs
        PRIVATE
        R_Type::R_Type_warnings
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
