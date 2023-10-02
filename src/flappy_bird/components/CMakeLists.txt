target_sources(flappy_bird PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Weight.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Jump.hpp
)

target_include_directories(flappy_bird PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
