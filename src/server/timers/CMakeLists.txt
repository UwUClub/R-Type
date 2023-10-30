target_sources(server PRIVATE
        Timer.hpp
        Timer.cpp
        Timer+SpawnEnemy.hpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
