include(cmake/SystemLink.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(R_Type_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(R_Type_setup_options)
  option(R_Type_ENABLE_HARDENING "Enable hardening" ON)
  option(R_Type_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    R_Type_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    R_Type_ENABLE_HARDENING
    OFF)

  R_Type_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR R_Type_PACKAGING_MAINTAINER_MODE)
    option(R_Type_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(R_Type_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(R_Type_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(R_Type_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(R_Type_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(R_Type_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(R_Type_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(R_Type_ENABLE_PCH "Enable precompiled headers" OFF)
    option(R_Type_ENABLE_CACHE "Enable ccache" On)
  else()
    option(R_Type_ENABLE_IPO "Enable IPO/LTO" ON)
    option(R_Type_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(R_Type_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(R_Type_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(R_Type_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(R_Type_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(R_Type_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(R_Type_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(R_Type_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(R_Type_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(R_Type_ENABLE_PCH "Enable precompiled headers" OFF)
    option(R_Type_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      R_Type_ENABLE_IPO
      R_Type_WARNINGS_AS_ERRORS
      R_Type_ENABLE_USER_LINKER
      R_Type_ENABLE_SANITIZER_ADDRESS
      R_Type_ENABLE_SANITIZER_LEAK
      R_Type_ENABLE_SANITIZER_UNDEFINED
      R_Type_ENABLE_SANITIZER_THREAD
      R_Type_ENABLE_SANITIZER_MEMORY
      R_Type_ENABLE_UNITY_BUILD
      R_Type_ENABLE_CLANG_TIDY
      R_Type_ENABLE_CPPCHECK
      R_Type_ENABLE_COVERAGE
      R_Type_ENABLE_PCH
      R_Type_ENABLE_CACHE)
  endif()

endmacro()

macro(R_Type_global_options)
  if(R_Type_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    R_Type_enable_ipo()
  endif()

  R_Type_supports_sanitizers()

  if(R_Type_ENABLE_HARDENING AND R_Type_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR R_Type_ENABLE_SANITIZER_UNDEFINED
       OR R_Type_ENABLE_SANITIZER_ADDRESS
       OR R_Type_ENABLE_SANITIZER_THREAD
       OR R_Type_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${R_Type_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${R_Type_ENABLE_SANITIZER_UNDEFINED}")
    R_Type_enable_hardening(R_Type_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(R_Type_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(R_Type_warnings INTERFACE)
  add_library(R_Type_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  R_Type_set_project_warnings(
    R_Type_warnings
    ${R_Type_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(R_Type_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(R_Type_options)
  endif()

  include(cmake/Sanitizers.cmake)
  R_Type_enable_sanitizers(
    R_Type_options
    ${R_Type_ENABLE_SANITIZER_ADDRESS}
    ${R_Type_ENABLE_SANITIZER_LEAK}
    ${R_Type_ENABLE_SANITIZER_UNDEFINED}
    ${R_Type_ENABLE_SANITIZER_THREAD}
    ${R_Type_ENABLE_SANITIZER_MEMORY})

  set_target_properties(R_Type_options PROPERTIES UNITY_BUILD ${R_Type_ENABLE_UNITY_BUILD})

  if(R_Type_ENABLE_PCH)
    target_precompile_headers(
      R_Type_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(R_Type_ENABLE_CACHE)
    message(WARNINGS "cache")
    include(cmake/Cache.cmake)
    R_Type_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(R_Type_ENABLE_CLANG_TIDY)
    R_Type_enable_clang_tidy(R_Type_options ${R_Type_WARNINGS_AS_ERRORS})
  endif()

  if(R_Type_ENABLE_CPPCHECK)
    R_Type_enable_cppcheck(${R_Type_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(R_Type_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    R_Type_enable_coverage(R_Type_options)
  endif()

  if(R_Type_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(R_Type_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(R_Type_ENABLE_HARDENING AND NOT R_Type_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR R_Type_ENABLE_SANITIZER_UNDEFINED
       OR R_Type_ENABLE_SANITIZER_ADDRESS
       OR R_Type_ENABLE_SANITIZER_THREAD
       OR R_Type_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    R_Type_enable_hardening(R_Type_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
