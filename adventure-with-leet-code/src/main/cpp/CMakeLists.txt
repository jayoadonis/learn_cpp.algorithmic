file(GLOB_RECURSE
  _PROJECT_ALL_PRIVATE_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.hxx
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/*.tpp)

file(GLOB_RECURSE
  _PROJECT_ALL_PUBLIC_CXX_MAIN_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.hxx
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/*.tpp)

add_library(${_PROJECT_TARGET_MAIN_NAME}
  ${_PROJECT_TARGET_MAIN_TYPE})

# REM: our.group::project_target_(app|static|shared|obj)
add_library(${_PROJECT_GROUP}::${_PROJECT_TARGET_MAIN_NAME}
  ALIAS ${_PROJECT_TARGET_MAIN_NAME})

# REM: for libraries intended to be consumed by other targets
target_compile_features(${_PROJECT_TARGET_MAIN_NAME}
  PUBLIC cxx_std_17)

include(GNUInstallDirs)

set_target_properties(${_PROJECT_TARGET_MAIN_NAME}
  PROPERTIES
  OUTPUT_NAME "$<LOWER_CASE:${_PROJECT_NAME}-${_PROJECT_VERSION}-$<$<CONFIG:Debug>:debug->${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}>"

  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${CMAKE_INSTALL_BINDIR}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${CMAKE_INSTALL_LIBDIR}
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${CMAKE_INSTALL_LIBDIR}

  # REM: for application/executable only targets, otherwise, use the 'target_compile_features'
  # CXX_STANDARD 17
  # CXX_STANDARD_REQUIRED ON
  # REM: all kind of targets
  CXX_EXTENSIONS OFF

  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON

  COMPILE_WARNING_AS_ERROR ${LCXXA_AWLEETCODE_FAIL_WARN})

# #REM: [Template Read-only Resources]
# if(WIN32)
# set(_PROJECT_RESOURCE_RELATIVE_DIR "resources")
# else()
# set(_PROJECT_RESOURCE_RELATIVE_DIR "../share/${_PROJECT_NAME}/resources")
# endif()
# target_compile_definitions(myapp PRIVATE
# LCXXA_AWLEETCODE_API_RES_REL_DIR="${_PROJECT_RESOURCE_RELATIVE_DIR}"
# )
if(NOT LCXXA_AWLEETCODE_TOGGLE_SHARED #[[AND NOT LCXXA_AWLEETCODE_MAIN_TOGGLE_SHARED]])
  target_compile_definitions(
    ${_PROJECT_TARGET_MAIN_NAME}
    PUBLIC
    LCXXA_AWLEETCODE_BUILD_STATIC)
else()
  target_compile_definitions(
    ${_PROJECT_TARGET_MAIN_NAME}
    PRIVATE
    LCXXA_AWLEETCODE_BUILD_EXPORT)
endif()

target_compile_options(${_PROJECT_TARGET_MAIN_NAME}
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4;/permissive->
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Wpedantic;-pedantic-errors>)

target_sources(${_PROJECT_TARGET_MAIN_NAME}
  PRIVATE
  ${_PROJECT_ALL_PRIVATE_CXX_MAIN_SOURCES}
  PUBLIC
  FILE_SET project_all_public_cxx_main_sources
  TYPE HEADERS
  BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/public
  FILES
  ${_PROJECT_ALL_PUBLIC_CXX_MAIN_SOURCES})

target_include_directories(${_PROJECT_TARGET_MAIN_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/private)

# REM: [BUILD TREE, PRE_BUILD] Runtime Resource Path Handling (Template, read-only)
target_compile_definitions(${_PROJECT_TARGET_MAIN_NAME}
  PRIVATE
  LCXXA_AWLEETCODE_REZ_DIR="${_PROJECT_RESOURCE_DESTINATION}")
add_custom_command(TARGET
  ${_PROJECT_TARGET_MAIN_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  "-DSRC_DIR=${PROJECT_SOURCE_DIR}/src/main/resources"
  "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_MAIN_NAME}>/${_PROJECT_RESOURCE_DESTINATION}"
  -P "${PROJECT_SOURCE_DIR}/cmake/sync-copy-paths-0.1.1-process.cmake"
  VERBATIM
  COMMENT "::: Synchronizing main resources")

# REM: [BUILD TREE, POST_BUILD] (Windows) shared libraries
if(WIN32 AND(LCXXA_AWLEETCODE_TOGGLE_SHARED #[[OR LCXXA_AWLEETCODE_MAIN_TOGGLE_SHARED]]))
  # get_target_property(_OUTPUT_NAME
  # ${_PROJECT_TARGET_MAIN_NAME} OUTPUT_NAME)
  add_custom_command(TARGET
    ${_PROJECT_TARGET_MAIN_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    "-DSRC_FILES=$<TARGET_RUNTIME_DLLS:${_PROJECT_TARGET_MAIN_NAME}>"
    "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_MAIN_NAME}>"

    # "-DMANIFEST_FILE=${CMAKE_CURRENT_BINARY_DIR}/.sync_copy_files_runtime_dlls.$<CONFIG>.manifest"
    # "-DMANIFEST_FILE=.sync_dlls_${_OUTPUT_NAME}.manifest"
    "-DMANIFEST_FILE=.sync_dlls_${_PROJECT_TARGET_MAIN_NAME}.$<CONFIG>.manifest"
    -P "${PROJECT_SOURCE_DIR}/cmake/sync-copy-files-0.1.1-process.cmake"
    VERBATIM
    COMMENT "::: Synchronizing Windows runtime dlls relative natively"
  )
endif()

if(BUILD_TESTING)
  add_library(${_PROJECT_TARGET_MAIN_NAME}_interface INTERFACE)
  add_library(${_PROJECT_GROUP}::${_PROJECT_TARGET_MAIN_NAME}_interface
    ALIAS ${_PROJECT_TARGET_MAIN_NAME}_interface)

  target_include_directories(${_PROJECT_TARGET_MAIN_NAME}_interface
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/private
  )

  target_link_libraries(${_PROJECT_TARGET_MAIN_NAME}_interface
    INTERFACE
    ${_PROJECT_GROUP}::${_PROJECT_TARGET_MAIN_NAME}
  )
endif()

# REM: [INSTALL & BUILD TREE for RPATH/RUNPATH] (Linux & macOS) shared libraries
if(UNIX)
  set_target_properties(${_PROJECT_TARGET_MAIN_NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib" # REM: Linux

    # BUILD_RPATH     "$ORIGIN/../lib"
  )

  if(APPLE)
    set_target_properties(${_PROJECT_TARGET_MAIN_NAME} PROPERTIES
      INSTALL_RPATH "@executable_path/../lib"

      # BUILD_RPATH "@executable_path/../lib"
    )
  endif()
endif()

install(TARGETS
  ${_PROJECT_TARGET_MAIN_NAME}
  EXPORT ${_PROJECT_NAME}_targets

  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT ${_PROJECT_NAME}_main

  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT ${_PROJECT_NAME}_main

  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  COMPONENT ${_PROJECT_NAME}_main

  FILE_SET project_all_public_cxx_main_sources
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT ${_PROJECT_NAME}_main)

install(EXPORT ${_PROJECT_NAME}_targets
  NAMESPACE ${_PROJECT_GROUP}::
  FILE ${_PROJECT_INSTALL_CONFIG_PREFIX_NAME}-targets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${_PROJECT_INSTALL_CONFIG_PREFIX_NAME}
  COMPONENT ${_PROJECT_NAME}_main)

# REM: [INSTALL] Runtime Path Resource Handling
install(
  DIRECTORY "${PROJECT_SOURCE_DIR}/src/main/resources/"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/${_PROJECT_NAME}/resources"
  COMPONENT "${_PROJECT_NAME}_main"
  PATTERN "*.keep" EXCLUDE
)