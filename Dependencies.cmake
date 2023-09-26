include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  find_package(Catch2)
  find_package(Boost COMPONENTS system asio)
  find_package(SDL2)

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  if (NOT TARGET Boost::boost OR NOT TARGET Boost::system OR NOT TARGET Boost::asio OR NOT TARGET Boost::serialization)
    CPMAddPackage(
            NAME Boost
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/boost"
            GIT_TAG "boost-1.83.0"
            OPTIONS
            "header_only"
            "system"
            "asio"
            "serialization"
    )
  endif()

  if (NOT TARGET SDL2::SDL2)
    CPMAddPackage(
            NAME sdl2
            VERSION 2.28.3
            GITHUB_REPOSITORY "libsdl-org/SDL"
            GIT_TAG "release-2.28.3"
    )
  endif()

endfunction()
