add_executable(client)
add_executable(server)
add_executable(flappybird)
add_library(rtype STATIC)

add_subdirectory(rtype)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(flappybird)
