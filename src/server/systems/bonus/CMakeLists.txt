target_sources(server PRIVATE
        System+MoveSpeed.cpp
)

target_link_libraries(server
        PRIVATE
        R_Type::R_Type_warnings
        ${Boost_LIBRARIES}
        rtype
        ecs
        Threads::Threads
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
)
