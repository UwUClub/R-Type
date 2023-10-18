target_sources(server PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ServerHandler.cpp"
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)
