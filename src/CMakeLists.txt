add_executable(client)
add_executable(server)
add_executable(flappy_bird)
add_library(ecs STATIC)
add_library(rtype_protocol STATIC)


add_subdirectory(ecs)
add_subdirectory(rtype_protocol)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(flappy_bird)
