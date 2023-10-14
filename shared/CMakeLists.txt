set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

# SDL
# https://github.com/libsdl-org/SDL
set( SDL_LIBC ON CACHE BOOL "" FORCE )
set( SDL_TEST OFF CACHE BOOL "" FORCE )
add_subdirectory( SDL )
target_link_libraries( ecs PRIVATE SDL2::SDL2main SDL2::SDL2-static )
target_link_libraries( rtype PRIVATE SDL2::SDL2main SDL2::SDL2-static )
target_link_libraries( client PRIVATE SDL2::SDL2main SDL2::SDL2-static )
target_link_libraries( server PRIVATE SDL2::SDL2main SDL2::SDL2-static )

# SDL_image
# https://github.com/libsdl-org/SDL_image
set( SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE )
add_subdirectory( SDL_image )
target_link_libraries( ecs PRIVATE SDL2_image::SDL2_image-static )
target_link_libraries( rtype PRIVATE SDL2_image::SDL2_image-static )
target_link_libraries( client PRIVATE SDL2_image::SDL2_image-static )
target_link_libraries( server PRIVATE SDL2_image::SDL2_image-static )