include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  #find_package(Catch2 QUIET)
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

endfunction()
