target_sources(server PRIVATE
        System+MoveMissiles.cpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
