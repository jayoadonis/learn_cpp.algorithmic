cmake_minimum_required(VERSION 3.24)
project("adventure-with-leet-code"
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)

if(WIN32)
  set(_HOME_DIR "$ENV{USERPROFILE}")
else()
  set(_HOME_DIR "$ENV{HOME}")
endif()

if(NOT _HOME_DIR)
  message(FATAL_ERROR "Could not resolve user home directory environment variable.")
endif()

if(NOT EXISTS "${_HOME_DIR}")
  message(FATAL_ERROR "The resolved home directory does not exist: ${_HOME_DIR}")
endif()

set(_PROJECT_GROUP "learn_cpp.algorithmic")
string(REGEX REPLACE "[ _.]" "-"
  _PROJECT_NAME "${PROJECT_NAME}")
string(TOLOWER "${_PROJECT_NAME}"
  _PROJECT_NAME)
set(_PROJECT_VERSION "${PROJECT_VERSION}")
set(_PROJECT_CANONICAL_BASE_NAME 
  "${_PROJECT_GROUP}.${_PROJECT_NAME}")

set(_PROJECT_TARGET_MAIN_NAME 
  "${_PROJECT_NAME}_target_main_static")
set(_PROJECT_TARGET_MAIN_TYPE "STATIC")

set(_PROJECT_TARGET_TEST_NAME
  "${_PROJECT_NAME}_target_test_app")

string(TOLOWER 
  "${_PROJECT_NAME}-${_PROJECT_TARGET_MAIN_TYPE}"
  _PROJECT_INSTALL_CONFIG_PREFIX_NAME)

file(TO_CMAKE_PATH 
  "${PROJECT_SOURCE_DIR}/out/install"
  _PROJECT_STAGING_PREFIX_PATH)

file(TO_CMAKE_PATH 
  "${_HOME_DIR}/.cmake/_precompiled_deps"
  _PROJECT_CACHE_DEPS_PREFIX_PATH)

option(LCXXA_AWLEETCODE_TOGGLE_SHARED "Toggle Shared (${_PROJECT_CANONICAL_BASE_NAME})" OFF)
option(LCXXA_AWLEETCODE_FAIL_WARN "Failure on warning (${_PROJECT_CANONICAL_BASE_NAME})" OFF)

set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH 
  "CMake Install Prefix (Currently overwritten by: '${_PROJECT_CANONICAL_BASE_NAME}')"
  FORCE)
set(CMAKE_STAGING_PREFIX_PATH
  "${_PROJECT_STAGING_PREFIX_PATH}" CACHE PATH 
  "CMake Staging Prefix (Currently overwritten by: '${_PROJECT_CANONICAL_BASE_NAME}')"
  FORCE)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "CMake Build Type (Currently overwritten by: '${_PROJECT_CANONICAL_BASE_NAME}')" FORCE)
endif()

if(LCXXA_AWLEETCODE_TOGGLE_SHARED)
  set(_PROJECT_TARGET_MAIN_NAME
    "${_PROJECT_NAME}_target_main_shared")
  set(_PROJECT_TARGET_MAIN_TYPE "SHARED")
  string(TOLOWER 
    "${_PROJECT_NAME}-${_PROJECT_TARGET_MAIN_TYPE}"
    _PROJECT_INSTALL_CONFIG_PREFIX_NAME)
endif()

list(APPEND CMAKE_PREFIX_PATH
  "${_PROJECT_CACHE_DEPS_PREFIX_PATH}"
  "${_PROJECT_STAGING_PREFIX_PATH}"
  "${_PROJECT_STAGING_PREFIX_PATH}/${_PROJECT_GROUP}/${_PROJECT_NAME}")

include(CTest)

add_subdirectory("src/main/cpp")

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory("src/test/cpp")
endif()

set(CPACK_PACKAGE_NAME ${_PROJECT_CANONICAL_BASE_NAME})
set(CPACK_PACKAGE_VERSION ${_PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR ${_PROJECT_GROUP})
set(CPACK_GENERATOR "ZIP;TGZ")
# set(CPACK_RESOURCES_FILE_LICENSE 
#   "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_VERBATIM_VARIABLES TRUE)

include(CPack)
