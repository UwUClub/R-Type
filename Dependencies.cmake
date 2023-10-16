include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(R_Type_setup_dependencies)

  #find_package(Catch2 QUIET)
  find_package(Boost QUIET COMPONENTS system serialization align assert config core static_assert throw_exception array bind chrono integer move mpl predef asio ratio type_traits typeof utility coroutine date_time function regex smart_ptr preprocessor io uuid QUIET)
  find_package(raylib)

<<<<<<< HEAD
#   if(NOT TARGET Catch2::Catch2WithMain)
#     CPMAddPackage(
#             NAME Catch2
#             VERSION 3.4.0
#             GITHUB_REPOSITORY catchorg/Catch2
#             GIT_TAG v3.4.0
#             GIT_SHALLOW TRUE
#     )
#   endif()
=======
  #if(NOT TARGET Catch2::Catch2WithMain)
   # CPMAddPackage(
    #        NAME Catch2
     #       VERSION 3.4.0
      #      GITHUB_REPOSITORY catchorg/Catch2
       #     GIT_TAG v3.4.0
        #    GIT_SHALLOW TRUE
    #)
  #endif()
>>>>>>> 7e7098225af0fd2bf4dff6298bf1d8de9b706d5d

  if (NOT TARGET Boost::system)
    CPMAddPackage(
            NAME boost_system
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/system"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::serialization)
    CPMAddPackage(
            NAME boost_serialization
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/serialization"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::assert)
    CPMAddPackage(
            NAME boost_assert
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/assert"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::config)
    CPMAddPackage(
            NAME boost_config
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/config"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::core)
    CPMAddPackage(
            NAME boost_core
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/core"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::align)
    CPMAddPackage(
            NAME boost_align
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/align"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::static_assert)
    CPMAddPackage(
            NAME boost_static_assert
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/static_assert"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::throw_exception)
    CPMAddPackage(
            NAME boost_throw_exception
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/throw_exception"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::array)
    CPMAddPackage(
            NAME boost_array
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/array"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::bind)
    CPMAddPackage(
            NAME boost_bind
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/bind"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::chrono)
    CPMAddPackage(
            NAME boost_chrono
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/chrono"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::integer)
    CPMAddPackage(
            NAME boost_integer
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/integer"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::move)
    CPMAddPackage(
            NAME boost_move
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/move"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::mpl)
    CPMAddPackage(
            NAME boost_mpl
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/mpl"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::predef)
    CPMAddPackage(
            NAME boost_predef
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/predef"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::asio)
    CPMAddPackage(
            NAME boost_asio
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/asio"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::ratio)
    CPMAddPackage(
            NAME boost_ratio
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/ratio"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::type_traits)
    CPMAddPackage(
            NAME boost_type_traits
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/type_traits"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::typeof)
    CPMAddPackage(
            NAME boost_typeof
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/typeof"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::utility)
    CPMAddPackage(
            NAME boost_utility
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/utility"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::coroutine)
    CPMAddPackage(
            NAME boost_coroutine
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/coroutine"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::date_time)
    CPMAddPackage(
            NAME boost_date_time
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/date_time"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::function)
    CPMAddPackage(
            NAME boost_function
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/function"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::regex)
    CPMAddPackage(
            NAME boost_regex
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/regex"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::smart_ptr)
    CPMAddPackage(
            NAME boost_smart_ptr
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/smart_ptr"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::preprocessor)
    CPMAddPackage(
            NAME boost_preprocessor
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/preprocessor"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::io)
    CPMAddPackage(
            NAME boost_io
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/io"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::uuid)
    CPMAddPackage(
            NAME boost_uuid
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/uuid"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::container_hash)
    CPMAddPackage(
            NAME boost_container_hash
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/container_hash"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::describe)
    CPMAddPackage(
            NAME boost_describe
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/describe"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::numeric_conversion)
    CPMAddPackage(
            NAME boost_numeric_conversion
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/numeric_conversion"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::mp11)
    CPMAddPackage(
            NAME boost_mp11
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/mp11"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::random)
    CPMAddPackage(
            NAME boost_random
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/random"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
  endif()

  if (NOT TARGET Boost::conversion)
    CPMAddPackage(
            NAME boost_conversion
            VERSION 1.83.0
            GITHUB_REPOSITORY "boostorg/conversion"
            GIT_TAG "boost-1.83.0"
            GIT_SHALLOW TRUE
    )
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


    set(RAYLIB_VERSION 4.5.0)
    find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
    if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
    endif()
    FetchContent_MakeAvailable(raylib)

endfunction()
