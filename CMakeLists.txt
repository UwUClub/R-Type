cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name and language
project(
  R_Type
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/UwUClub/R-Type"
  LANGUAGES CXX C)

include(cmake/PreventInSourceBuilds.cmake)
include(ProjectOptions.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
R_Type_setup_options()

R_Type_global_options()
include(Dependencies.cmake)
R_Type_setup_dependencies()

R_Type_local_options()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA this build was generated from")
string(
  SUBSTRING "${GIT_SHA}"
            0
            8
            GIT_SHORT_SHA)

target_compile_features(R_Type_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

add_library(R_Type::R_Type_options ALIAS R_Type_options)
add_library(R_Type::R_Type_warnings ALIAS R_Type_warnings)

#add_library(R_Type::R_Type_options INTERFACE IMPORTED)
#add_library(R_Type::R_Type_warnings INTERFACE IMPORTED)

# Adding the src:
add_subdirectory(src)

# Don't even look at tests if we're not top level
if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

# Adding the tests:
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT server)

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(cmake/PackageProject.cmake)
find_package(Boost)

# Add other targets that you want installed here, by default we just package the one executable
# we know we want to ship
R_Type_package_project(
  TARGETS
  server
  client
  R_Type_options
  R_Type_warnings
)
# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
install(TARGETS server client
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "RTYPE")
if(NOT DEFINED CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "RTYPE")
set(CPACK_PACKAGE_CONTACT "UwU Club")

if(WIN32)
    set(CPACK_GENERATOR "NSIS64")
else()
    set(CPACK_GENERATOR "DEB;RPM")
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CPack)
