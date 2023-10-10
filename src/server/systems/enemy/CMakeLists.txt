find_package(Boost REQUIRED COMPONENTS system thread serialization)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

target_sources(server PRIVATE
        System+SpawnEnemy.cpp
        System+MoveEnemy.cpp
        System+EnemyShoot.cpp
        System+EnemyHit.cpp
        System+KillEnemy.cpp
)

target_link_libraries(server
        PRIVATE R_Type::R_Type_options
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

set_target_properties(server PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
