target_sources(server PRIVATE
        System+HandleClientCrash.cpp
        System+ReceiveAknowledgment.cpp
)

target_include_directories(server PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
