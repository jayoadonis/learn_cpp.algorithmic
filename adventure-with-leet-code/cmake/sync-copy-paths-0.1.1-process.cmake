#[[ sync-copy-paths-0.1.1-process.cmake
add_custom_command(TARGET
  ${_PROJECT_TARGET_TEST_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  "-DSRC_DIR=${PROJECT_SOURCE_DIR}/src/test/resources"
  "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_TEST_NAME}>/../${_PROJECT_RESOURCE_DESTINATION}"
  -P "${PROJECT_SOURCE_DIR}/cmake/sync-copy-paths-0.1.0-process.cmake"
  VERBATIM
  COMMENT "::: Synchronizing test resources"
)
]]

if(NOT DEFINED SRC_DIR)
  message(FATAL_ERROR "SRC_DIR is required")
endif()

if(NOT DEFINED DST_DIR)
  message(FATAL_ERROR "DST_DIR is required")
endif()

get_filename_component(SRC_DIR "${SRC_DIR}" ABSOLUTE)
get_filename_component(DST_DIR "${DST_DIR}" ABSOLUTE)

if(NOT IS_DIRECTORY "${SRC_DIR}")
  message(FATAL_ERROR "SRC_DIR is not a directory: ${SRC_DIR}")
endif()

file(MAKE_DIRECTORY "${DST_DIR}")

message(STATUS "Synchronizing paths (Paths symlink/copy):")
message(STATUS "  source:      ${SRC_DIR}")
message(STATUS "  destination: ${DST_DIR}")

file(GLOB_RECURSE _src_rel_paths
  LIST_DIRECTORIES true
  RELATIVE "${SRC_DIR}"
  "${SRC_DIR}/*"
)

set(_curr_src_rel_filepaths)

foreach(_src_rel_path IN LISTS _src_rel_paths)
  set(_src_abs_path "${SRC_DIR}/${_src_rel_path}")
  set(_dst_abs_path "${DST_DIR}/${_src_rel_path}")

  if(IS_DIRECTORY "${_src_abs_path}")
    continue()
  endif()

  set(_src_abs_filepath "${_src_abs_path}")
  set(_dst_abs_filepath "${_dst_abs_path}")
  set(_src_rel_filepath "${_src_rel_path}")

  get_filename_component(_src_rel_dir "${_src_rel_filepath}" DIRECTORY)

  if(_src_rel_dir)
    file(MAKE_DIRECTORY "${DST_DIR}/${_src_rel_dir}")
  endif()

  list(APPEND _curr_src_rel_filepaths "${_src_rel_filepath}")

  #REM: Incremental logic
  set(_needs_update FALSE)

  if(IS_SYMLINK "${_dst_abs_filepath}")
    #REM: Check if symlink points to the correct source
    file(READ_SYMLINK "${_dst_abs_filepath}" _existing_target)

    #REM: Normalize for comparison (handle relative/absolute)
    get_filename_component(_existing_target_abs "${_existing_target}" ABSOLUTE
      BASE_DIR "${DST_DIR}/${_src_rel_dir}")

    if(NOT _existing_target_abs STREQUAL "${_src_abs_filepath}")
      set(_needs_update TRUE)
    endif()
  elseif(EXISTS "${_dst_abs_filepath}")
    #REM: Regular file exists -> use copy_if_different to update only when changed
    execute_process(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different
      "${_src_abs_filepath}" "${_dst_abs_filepath}"
      RESULT_VARIABLE _copy_result
    )

    if(NOT _copy_result EQUAL 0)
      message(FATAL_ERROR "Failed to update ${_dst_abs_filepath}")
    endif()
  else()
    #REM: Destination does not exist -> try symlink, then copy fallback
    file(CREATE_LINK
      "${_src_abs_filepath}" "${_dst_abs_filepath}"
      RESULT _link_result
      SYMBOLIC
      COPY_ON_ERROR)

    if(NOT _link_result EQUAL 0)
      message(FATAL_ERROR "Failed to link/copy ${_src_abs_filepath} -> ${_dst_abs_filepath}")
    endif()
  endif()

  if(_needs_update)
    #REM: Symlink exists but points to wrong target -> replace it
    file(REMOVE "${_dst_abs_filepath}")
    file(CREATE_LINK
      "${_src_abs_filepath}" "${_dst_abs_filepath}"
      RESULT _link_result
      SYMBOLIC
      COPY_ON_ERROR)

    if(NOT _link_result EQUAL 0)
      message(FATAL_ERROR "Failed to replace link ${_dst_abs_filepath}")
    endif()
  endif()
endforeach()

#REM: Stale file removal
file(GLOB_RECURSE _dst_rel_paths
  LIST_DIRECTORIES true
  RELATIVE "${DST_DIR}"
  "${DST_DIR}/*"
)

foreach(_dst_rel_path IN LISTS _dst_rel_paths)
  set(_dst_abs_path "${DST_DIR}/${_dst_rel_path}")

  if(IS_DIRECTORY "${_dst_abs_path}")
    continue()
  endif()

  list(FIND _curr_src_rel_filepaths "${_dst_rel_path}" _idx)

  if(_idx EQUAL -1)
    message(STATUS "Removing stale file: ${_dst_abs_path}")
    file(REMOVE "${_dst_abs_path}")
  endif()
endforeach()

#REM: Remove empty directories
set(_is_remove TRUE)

while(_is_remove)
  set(_is_remove FALSE)

  file(GLOB_RECURSE _dst_rel_paths
    LIST_DIRECTORIES true
    RELATIVE "${DST_DIR}"
    "${DST_DIR}/*"
  )

  foreach(_dst_rel_path IN LISTS _dst_rel_paths)
    set(_dst_abs_path "${DST_DIR}/${_dst_rel_path}")

    if(NOT IS_DIRECTORY "${_dst_abs_path}")
      continue()
    endif()

    if(IS_SYMLINK "${_dst_abs_path}")
      continue()
    endif()

    file(GLOB _dst_abs_subpath_pattern "${_dst_abs_path}/*")

    if(NOT _dst_abs_subpath_pattern)
      message(STATUS "Removing empty directory: ${_dst_abs_path}")
      file(REMOVE_RECURSE "${_dst_abs_path}")
      set(_is_remove TRUE)
    endif()
  endforeach()
endwhile()

message(STATUS "Synchronization (Paths) complete.")