set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

find_package(Boost REQUIRED)

target_sources(ecs PRIVATE
        World.hpp
        SparseArray.hpp
)

add_subdirectory(Event)

target_link_libraries(ecs
        PRIVATE R_Type::R_Type_options
        R_Type::R_Type_warnings
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image
        ${Boost_LIBRARIES}
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Event")
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ecs PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(client PRIVATE "../../build/_deps/sdl2_image-src/include")
target_include_directories(server PRIVATE "../../build/_deps/sdl2_image-src/include")


set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
