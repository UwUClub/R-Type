set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(flappybird PRIVATE
        main.cpp
        SDLDisplayClass.cpp
        ConfigReader.cpp
)

add_subdirectory(components)
add_subdirectory(systems)

target_link_libraries(flappybird PRIVATE
        SDL2::SDL2main
        SDL2::SDL2
        SDL2_image
        ecs
        nlohmann_json
)


target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(flappybird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/components)
target_include_directories(flappybird PRIVATE "../../build/_deps/sdl2-src/include/SDL2")
target_include_directories(flappybird PRIVATE "../../build/_deps/sdl2_image-src/include")

set_target_properties(flappybird PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
