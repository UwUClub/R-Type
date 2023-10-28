add_subdirectory(network)
add_subdirectory(player)
add_subdirectory(enemy)
add_subdirectory(missile)
add_subdirectory(bonus)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
