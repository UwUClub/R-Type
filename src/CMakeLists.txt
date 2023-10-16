add_executable(client)
add_executable(server)
add_executable(flappy_bird)
add_library(ecs STATIC)
add_library(rtype STATIC)


add_subdirectory(ecs)
add_subdirectory(rtype)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(flappy_bird)
