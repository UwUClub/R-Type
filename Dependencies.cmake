include(cmake/CPM.cmake)
include(FetchContent)
include(cmake/FindSDL2.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  find_package(Catch2 QUIET)
  find_package(Boost COMPONENTS system serialization align assert config core static_assert throw_exception array bind chrono integer move mpl predef asio ratio type_traits typeof utility coroutine date_time function regex smart_ptr preprocessor io)
  find_package(SDL2)

  if(NOT TARGET Catch2::Catch2WithMain)
    CPMAddPackage(
            NAME Catch2
            VERSION 3.4.0
            GITHUB_REPOSITORY catchorg/Catch2
            GIT_TAG v3.4.0
    )
  endif()

  if (NOT TARGET Boost::boost)
    CPMAddPackage(
            NAME Boost
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/boost"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::system)
    CPMAddPackage(
            NAME boost_system
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/system"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::serialization)
    CPMAddPackage(
            NAME boost_serialization
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/serialization"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::assert)
    CPMAddPackage(
            NAME boost_assert
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/assert"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::config)
    CPMAddPackage(
            NAME boost_config
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/config"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::core)
    CPMAddPackage(
            NAME boost_core
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/core"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::align)
    CPMAddPackage(
            NAME boost_align
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/align"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::static_assert)
    CPMAddPackage(
            NAME boost_static_assert
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/static_assert"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::throw_exception)
    CPMAddPackage(
            NAME boost_throw_exception
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/throw_exception"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::array)
    CPMAddPackage(
            NAME boost_array
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/array"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::bind)
    CPMAddPackage(
            NAME boost_bind
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/bind"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::chrono)
    CPMAddPackage(
            NAME boost_chrono
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/chrono"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::integer)
    CPMAddPackage(
            NAME boost_integer
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/integer"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::move)
    CPMAddPackage(
            NAME boost_move
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/move"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::mpl)
    CPMAddPackage(
            NAME boost_mpl
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/mpl"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::predef)
    CPMAddPackage(
            NAME boost_predef
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/predef"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::asio)
    CPMAddPackage(
            NAME boost_asio
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/asio"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::ratio)
    CPMAddPackage(
            NAME boost_ratio
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/ratio"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::type_traits)
    CPMAddPackage(
            NAME boost_type_traits
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/type_traits"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::typeof)
    CPMAddPackage(
            NAME boost_typeof
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/typeof"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::utility)
    CPMAddPackage(
            NAME boost_utility
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/utility"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::coroutine)
    CPMAddPackage(
            NAME boost_coroutine
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/coroutine"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::date_time)
    CPMAddPackage(
            NAME boost_date_time
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/date_time"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::function)
    CPMAddPackage(
            NAME boost_function
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/function"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::regex)
    CPMAddPackage(
            NAME boost_regex
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/regex"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::smart_ptr)
    CPMAddPackage(
            NAME boost_smart_ptr
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/smart_ptr"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::preprocessor)
    CPMAddPackage(
            NAME boost_preprocessor
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/preprocessor"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  if (NOT TARGET Boost::io)
    CPMAddPackage(
            NAME boost_io
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/io"
            GIT_TAG "boost-1.83.0"
    )
  endif()

  Set(FETCHCONTENT_QUIET FALSE)

  if (NOT TARGET SDL2::SDL2)
    FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.26.3
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL2)
    set(SDL2_DOWNLOADED TRUE)
  endif()

  if (NOT TARGET SLD2_image)
    FetchContent_Declare(
            SDL2_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-2.6.3
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
  endif()

  # START ADDITION
  set(SDL2IMAGE_INSTALL OFF)
  set(BUILD_SHARED_LIBS FALSE)
  # END ADDITION

  FetchContent_MakeAvailable(SDL2_image)

endfunction()
