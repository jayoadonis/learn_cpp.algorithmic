include(FetchContent)

set(CATCH_INSTALL_DOCS OFF CACHE INTERNAL
  "Disable Catch2 docs generation" FORCE)
set(CATCH_ENABLE_WERROR OFF CACHE INTERNAL
  "Do not treat Catch2 warnings as errors" FORCE)
set(BUILD_TESTING OFF CACHE INTERNAL
  "Disable Catch2 internal tests" FORCE)
set(CATCH_BUILD_EXAMPLES OFF CACHE INTERNAL
  "Disable Catch2 examples" FORCE)
set(CATCH_BUILD_BENCHMARKING OFF CACHE INTERNAL
  "Disable Catch2 benchmarking" FORCE)
set(CATCH_BUILD_SURROGATE_HEADERS OFF CACHE INTERNAL
  "Disable Catch2 surrogate headers" FORCE)
set(CATCH_CONFIG_DEFAULT_REPORTER "console" CACHE INTERNAL
  "Optimize for console reporter" FORCE)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
  GIT_TAG "v3.15.3"
  GIT_SHALLOW ON
  GIT_PROGRESS ON
  TIMEOUT 20
)
set(_OLD_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

set(BUILD_SHARED_LIBS ON CACHE INTERNAL
  "Force shared build for Catch2" FORCE)

FetchContent_MakeAvailable(Catch2)

set(BUILD_SHARED_LIBS ${_OLD_BUILD_SHARED_LIBS} CACHE INTERNAL "" FORCE)

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)

file(GLOB_RECURSE
  _PROJECT_ALL_PRIVATE_CXX_TEST_SOURCES
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.hxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/private/*.tpp"
)

add_executable(${_PROJECT_TARGET_TEST_NAME})

set_target_properties(${_PROJECT_TARGET_TEST_NAME}
  PROPERTIES
  OUTPUT_NAME "$<LOWER_CASE:${_PROJECT_NAME}-${_PROJECT_VERSION}-$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}>"

  #REM: for application/executable only targets
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  #REM: all kind of targets
  CXX_EXTENSIONS OFF

  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON

  COMPILE_WARNING_AS_ERROR ${LCXXA_AWLEETCODE_FAIL_WARN}
)

target_compile_options(${_PROJECT_TARGET_TEST_NAME}
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Wpedantic;-pedantic-errors>

  # REM: vanilla testing with std assert
  # $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/UNDEBUG>
  # $<$<AND:$<CONFIG:Release>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-UNDEBUG>
)

target_sources(${_PROJECT_TARGET_TEST_NAME}
  PRIVATE
  ${_PROJECT_ALL_PRIVATE_CXX_TEST_SOURCES}
)

target_include_directories(${_PROJECT_TARGET_TEST_NAME} BEFORE
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/private"
  "${PROJECT_SOURCE_DIR}/src/main/cpp/private"
)

target_link_libraries(${_PROJECT_TARGET_TEST_NAME}
  PRIVATE
  ${_PROJECT_GROUP}::${_PROJECT_TARGET_MAIN_NAME}
  Catch2::Catch2
)

target_compile_definitions(${_PROJECT_TARGET_TEST_NAME}
  PRIVATE
  CATCH_CONFIG_FAST_COMPILE
)

catch_discover_tests(${_PROJECT_TARGET_TEST_NAME}
  DISCOVERY_MODE PRE_TEST # REM: Prevents post-build script failures from killing the compiler run
  ADD_TAGS_AS_LABELS
  PROPERTIES
  LABELS "all"
)

#REM: [PRE_BUILD] Runtime Path Resource Handling
add_custom_command(TARGET
  ${_PROJECT_TARGET_TEST_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  "-DSRC_DIR=${PROJECT_SOURCE_DIR}/src/test/resources"
  "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_TEST_NAME}>/resources"
  -P "${PROJECT_SOURCE_DIR}/cmake/sync-copy-paths-0.1.0-process.cmake"
  VERBATIM
  COMMENT "::: Synchronizing test resources"
)

if(WIN32 #[[AND LCXXA_AWLEETCODE_TOGGLE_SHARED]])
  # get_target_property(_OUTPUT_NAME 
  #   ${_PROJECT_TARGET_TEST_NAME} OUTPUT_NAME)

  add_custom_command(TARGET
    ${_PROJECT_TARGET_TEST_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    "-DSRC_FILES=$<TARGET_RUNTIME_DLLS:${_PROJECT_TARGET_TEST_NAME}>"
    "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_TEST_NAME}>"
    # "-DMANIFEST_FILE=${CMAKE_CURRENT_BINARY_DIR}/.sync_copy_files_runtime_dlls.$<CONFIG>.manifest"
    # "-DMANIFEST_FILE=.sync_dlls_${_OUTPUT_NAME}.manifest"
    "-DMANIFEST_FILE=.sync_dlls_${_PROJECT_TARGET_TEST_NAME}.$<CONFIG>.manifest"
    -P "${PROJECT_SOURCE_DIR}/cmake/sync-copy-files-0.1.1-process.cmake"
    VERBATIM
    COMMENT "::: Synchronizing Windows runtime dlls relative to test executable natively"
  )
endif()