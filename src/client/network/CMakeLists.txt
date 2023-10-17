target_sources(client PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientHandler.cpp"
)

target_include_directories(client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)
