target_sources(RenderPlugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SFMLDisplayClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigReader.cpp
    )

target_link_libraries(RenderPlugin
    PRIVATE
    R_Type::R_Type_warnings
    sfml-graphics
    sfml-window
    sfml-system
    ecs
    ${Boost_LIBRARIES}
    Boost::asio
    Boost::serialization
    Boost::uuid
    nlohmann_json
)
target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Event PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


set_target_properties(RenderPlugin PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
