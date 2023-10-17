include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  #find_package(Catch2 QUIET)
  set(BOOST_VERSION "1.83.0")
  find_package(Boost ${BOOST_VERSION} QUIET)

  #if(NOT TARGET Catch2::Catch2WithMain)
   # CPMAddPackage(
    #        NAME Catch2
     #       VERSION 3.4.0
      #      GITHUB_REPOSITORY catchorg/Catch2
       #     GIT_TAG v3.4.0
        #    GIT_SHALLOW TRUE
    #)
  #endif()

  set(FETCHCONTENT_QUIET FALSE)

  if (NOT TARGET Boost::boost)
    FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}.7z
        USES_TERMINAL_DOWNLOAD TRUE
        GIT_PROGRESS TRUE
        DOWNLOAD_NO_EXTRACT FALSE
    )
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    add_definitions(-DBOOST_USE_WINDOWS_H=0)
    FetchContent_MakeAvailable(Boost)
  endif()

  if (NOT TARGET SDL2)
    FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.28.3
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DSDL_STATIC=ON
    )
  endif()
  FetchContent_MakeAvailable(SDL2)
  install(TARGETS SDL2-static
          EXPORT SDL2Targets
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          INCLUDES DESTINATION include
          PUBLIC_HEADER DESTINATION include
          )

  if (NOT TARGET SDL2_image::SDL2_image)
    FetchContent_Declare(
            SDL2_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-2.6.3
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DSDL_STATIC=ON
    )
    set(SDL2IMAGE_INSTALL OFF)
    FetchContent_MakeAvailable(SDL2_image)
  endif()

endfunction()
