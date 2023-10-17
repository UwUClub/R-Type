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

  if (NOT TARGET Boost::dynamic_bitset)
    CPMAddPackage(
            NAME boost_dynamic_bitset
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/dynamic_bitset"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::tti)
    CPMAddPackage(
            NAME boost_tti
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/tti"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::function_types)
    CPMAddPackage(
            NAME boost_function_types
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/function_types"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::winapi)
    CPMAddPackage(
            NAME boost_winapi
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/winapi"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::detail)
    CPMAddPackage(
            NAME boost_detail
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/detail"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::range)
    CPMAddPackage(
            NAME boost_range
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/range"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::concept_check)
    CPMAddPackage(
            NAME boost_concept_check
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/concept_check"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::iterator)
    CPMAddPackage(
            NAME boost_iterator
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/iterator"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::fusion)
    CPMAddPackage(
            NAME boost_fusion
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/fusion"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::optional)
    CPMAddPackage(
            NAME boost_optional
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/optional"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::tuple)
    CPMAddPackage(
            NAME boost_tuple
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/tuple"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::functional)
    CPMAddPackage(
            NAME boost_functional
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/functional"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::variant2)
    CPMAddPackage(
            NAME boost_variant2
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/variant2"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::spirit)
    CPMAddPackage(
            NAME boost_spirit
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/spirit"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::rational)
    CPMAddPackage(
            NAME boost_rational
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/rational"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::context)
    CPMAddPackage(
            NAME boost_context
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/context"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::algorithm)
    CPMAddPackage(
            NAME boost_algorithm
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/algorithm"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::exception)
    CPMAddPackage(
            NAME boost_exception
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/exception"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::lexical_cast)
    CPMAddPackage(
            NAME boost_lexical_cast
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/lexical_cast"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::endian)
    CPMAddPackage(
            NAME boost_endian
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/endian"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if(NOT TARGET Boost::pool)
    CPMAddPackage(
            NAME boost_pool
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/pool"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::exception)
    CPMAddPackage(
            NAME boost_exception
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/exception"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::unordered)
    CPMAddPackage(
            NAME boost_unordered
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/unordered"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::tokenizer)
    CPMAddPackage(
            NAME boost_tokenizer
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/tokenizer"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::phoenix)
    CPMAddPackage(
            NAME boost_phoenix
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/phoenix"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::unordered)
    CPMAddPackage(
            NAME boost_unordered
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/unordered"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::container)
    CPMAddPackage(
            NAME boost_container
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/container"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::variant)
    CPMAddPackage(
            NAME boost_variant
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/variant"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::proto)
    CPMAddPackage(
            NAME boost_proto
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/proto"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::intrusive)
    CPMAddPackage(
            NAME boost_intrusive
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/intrusive"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::thread)
    CPMAddPackage(
            NAME boost_thread
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/thread"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::type_index)
    CPMAddPackage(
            NAME boost_type_index
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/type_index"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::atomic)
    CPMAddPackage(
            NAME boost_atomic
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/atomic"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET nlohmann_json)
    CPMAddPackage(
            NAME nlohmann_json
            VERSION 3.11.2
            GITHUB_REPOSITORY "nlohmann/json"
            GIT_TAG v3.11.2
            GIT_SHALLOW TRUE
    )
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
