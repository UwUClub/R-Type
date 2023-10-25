include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  #find_package(Catch2 QUIET)
  set(BOOST_VERSION "1.83.0")
  set(BOOST_LIBS system serialization align assert config core static_assert throw_exception array bind chrono integer move mpl predef asio ratio type_traits typeof utility coroutine date_time function regex smart_ptr preprocessor io uuid)
  # set no header
  set(BOOST_INCLUDE_LIBRARIES ${BOOST_LIBS})
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

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
    FetchContent_MakeAvailable(Boost)

endfunction()
