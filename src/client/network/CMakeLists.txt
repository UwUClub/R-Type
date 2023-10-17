target_sources(client PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientHandler.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ClientHandler.cpp"
)

target_link_libraries(client
        PRIVATE
        ${Boost_LIBRARIES}
        Boost::asio
        Boost::serialization
        Boost::serialization
        Boost::uuid
)

target_include_directories(client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)
