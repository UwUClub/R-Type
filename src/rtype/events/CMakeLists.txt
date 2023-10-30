target_sources(rtype PRIVATE
        ClientGameEvent.hpp
        ClientGameEvent.cpp
        ServerGameEvent.hpp
        ServerGameEvent.cpp
)

target_include_directories(rtype PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
