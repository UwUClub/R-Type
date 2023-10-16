find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_subdirectory(player)
add_subdirectory(bot)
add_subdirectory(enemy)
add_subdirectory(missile)
add_subdirectory(bonus)
add_subdirectory(background)
add_subdirectory(graphic)

target_sources(client PRIVATE
        System.hpp
)

target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(client PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
