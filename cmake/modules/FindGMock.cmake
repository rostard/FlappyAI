# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindGMock
# ---------
#
# Locate the Google C++ Mocking Framework.
#
# Imported targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the following :prop_tgt:`IMPORTED` targets:
#
# ``GMock::GMock``
#   The Google Test ``GMock`` library, if found; adds Thread::Thread
#   automatically
# ``GMock::Main``
#   The Google Test ``GMock_main`` library, if found
#
#
# Result variables
# ^^^^^^^^^^^^^^^^
#
# This module will set the following variables in your project:
#
# ``GMock_FOUND``
#   Found the Google Testing framework
# ``GMock_INCLUDE_DIRS``
#   the directory containing the Google Test headers
#
# The library variables below are set as normal variables.  These
# contain debug/optimized keywords when a debugging library is found.
#
# ``GMock_LIBRARIES``
#   The Google Test ``GMock`` library; note it also requires linking
#   with an appropriate thread library
# ``GMock_MAIN_LIBRARIES``
#   The Google Test ``GMock_main`` library
# ``GMock_BOTH_LIBRARIES``
#   Both ``GMock`` and ``GMock_main``
#
# Cache variables
# ^^^^^^^^^^^^^^^
#
# The following cache variables may also be set:
#
# ``GMock_ROOT``
#   The root directory of the Google Test installation (may also be
#   set as an environment variable)
# ``GMock_MSVC_SEARCH``
#   If compiling with MSVC, this variable can be set to ``MT`` or
#   ``MD`` (the default) to enable searching a GMock build tree
#
#
# Example usage
# ^^^^^^^^^^^^^
#
# ::
#
#     enable_testing()
#     find_package(GMock REQUIRED)
#
#     add_executable(foo foo.cc)
#     target_link_libraries(foo GMock::GMock GMock::Main)
#
#     add_test(AllTestsInFoo foo)
#
#
function(_GMock_append_debugs _endvar _library)
    if(${_library} AND ${_library}_DEBUG)
        set(_output optimized ${${_library}} debug ${${_library}_DEBUG})
    else()
        set(_output ${${_library}})
    endif()
    set(${_endvar} ${_output} PARENT_SCOPE)
endfunction()

function(_GMock_find_library _name)
    find_library(${_name}
        NAMES ${ARGN}
        HINTS
            ENV GMock_ROOT
            ${GMock_ROOT}
        PATH_SUFFIXES ${_GMock_libpath_suffixes}
    )
    mark_as_advanced(${_name})
endfunction()

#

if(NOT DEFINED GMock_MSVC_SEARCH)
    set(GMock_MSVC_SEARCH MD)
endif()

set(_GMock_libpath_suffixes lib)
if(MSVC)
    if(GMock_MSVC_SEARCH STREQUAL "MD")
        list(APPEND _GMock_libpath_suffixes
            msvc/GMock-md/Debug
            msvc/GMock-md/Release
            msvc/x64/Debug
            msvc/x64/Release
            )
    elseif(GMock_MSVC_SEARCH STREQUAL "MT")
        list(APPEND _GMock_libpath_suffixes
            msvc/GMock/Debug
            msvc/GMock/Release
            msvc/x64/Debug
            msvc/x64/Release
            )
    endif()
endif()


find_path(GMock_INCLUDE_DIR GMock/GMock.h
    HINTS
        $ENV{GMock_ROOT}/include
        ${GMock_ROOT}/include
)
mark_as_advanced(GMock_INCLUDE_DIR)

if(MSVC AND GMock_MSVC_SEARCH STREQUAL "MD")
    # The provided /MD project files for Google Test add -md suffixes to the
    # library names.
    _GMock_find_library(GMock_LIBRARY            GMock-md  GMock)
    _GMock_find_library(GMock_LIBRARY_DEBUG      GMock-mdd GMockd)
    _GMock_find_library(GMock_MAIN_LIBRARY       GMock_main-md  GMock_main)
    _GMock_find_library(GMock_MAIN_LIBRARY_DEBUG GMock_main-mdd GMock_maind)
else()
    _GMock_find_library(GMock_LIBRARY            GMock)
    _GMock_find_library(GMock_LIBRARY_DEBUG      GMockd)
    _GMock_find_library(GMock_MAIN_LIBRARY       GMock_main)
    _GMock_find_library(GMock_MAIN_LIBRARY_DEBUG GMock_maind)
endif()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GMock DEFAULT_MSG GMock_LIBRARY GMock_INCLUDE_DIR GMock_MAIN_LIBRARY)

if(GMock_FOUND)
    set(GMock_INCLUDE_DIRS ${GMock_INCLUDE_DIR})
    _GMock_append_debugs(GMock_LIBRARIES      GMock_LIBRARY)
    _GMock_append_debugs(GMock_MAIN_LIBRARIES GMock_MAIN_LIBRARY)
    set(GMock_BOTH_LIBRARIES ${GMock_LIBRARIES} ${GMock_MAIN_LIBRARIES})

    include(CMakeFindDependencyMacro)

    if(NOT TARGET GMock::GMock)
        add_library(GMock::GMock UNKNOWN IMPORTED)
        set_target_properties(GMock::GMock PROPERTIES
            INTERFACE_LINK_LIBRARIES "Threads::Threads")
        if(GMock_INCLUDE_DIRS)
            set_target_properties(GMock::GMock PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${GMock_INCLUDE_DIRS}")
        endif()
        if(EXISTS "${GMock_LIBRARY}")
            set_target_properties(GMock::GMock PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                IMPORTED_LOCATION "${GMock_LIBRARY}")
        endif()
        if(EXISTS "${GMock_LIBRARY_RELEASE}")
            set_property(TARGET GMock::GMock APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE)
            set_target_properties(GMock::GMock PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                IMPORTED_LOCATION_RELEASE "${GMock_LIBRARY_RELEASE}")
        endif()
        if(EXISTS "${GMock_LIBRARY_DEBUG}")
            set_property(TARGET GMock::GMock APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG)
            set_target_properties(GMock::GMock PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
                IMPORTED_LOCATION_DEBUG "${GMock_LIBRARY_DEBUG}")
        endif()
      endif()
      if(NOT TARGET GMock::Main)
          add_library(GMock::Main UNKNOWN IMPORTED)
          set_target_properties(GMock::Main PROPERTIES
              INTERFACE_LINK_LIBRARIES "GMock::GMock")
          if(EXISTS "${GMock_MAIN_LIBRARY}")
              set_target_properties(GMock::Main PROPERTIES
                  IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
                  IMPORTED_LOCATION "${GMock_MAIN_LIBRARY}")
          endif()
          if(EXISTS "${GMock_MAIN_LIBRARY_RELEASE}")
            set_property(TARGET GMock::Main APPEND PROPERTY
                IMPORTED_CONFIGURATIONS RELEASE)
            set_target_properties(GMock::Main PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                IMPORTED_LOCATION_RELEASE "${GMock_MAIN_LIBRARY_RELEASE}")
          endif()
          if(EXISTS "${GMock_MAIN_LIBRARY_DEBUG}")
            set_property(TARGET GMock::Main APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG)
            set_target_properties(GMock::Main PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
                IMPORTED_LOCATION_DEBUG "${GMock_MAIN_LIBRARY_DEBUG}")
          endif()
    endif()
endif()
