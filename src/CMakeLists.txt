add_executable(client)
add_executable(server)
add_library(ecs STATIC)
add_library(rtype STATIC)


add_subdirectory(ecs)
add_subdirectory(rtype)
add_subdirectory(server)
add_subdirectory(client)
