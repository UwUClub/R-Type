cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# Set the project name and language
project(
  R_Type
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/UwUClub/R-Type"
  LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(R_Type_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
R_Type_set_project_warnings(
        R_Type_warnings
        FALSE
        ""
        ""
        ""
        "")

include(Dependencies.cmake)
R_Type_setup_dependencies()

include(cmake/StandardProjectSettings.cmake)

add_library(R_Type::R_Type_warnings ALIAS R_Type_warnings)

# Adding the src:
add_subdirectory(src)

# Adding the tests:
# include(CTest)

# if(BUILD_TESTING)
#   add_subdirectory(test)
# endif()

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  include(cmake/Utilities.cmake)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  get_all_installable_targets(all_targets)
  message("all_targets=${all_targets}")
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT server)

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