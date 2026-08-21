
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

message(STATUS "Synchronizing paths:")
message(STATUS "  source:      ${SRC_DIR}")
message(STATUS "  destination: ${DST_DIR}")

#REM: Gather all source entries (files and directories) relative to SRC_DIR.
#REM: pattern paths: relative filepaths & directories/folders
file(GLOB_RECURSE _src_rel_paths
  LIST_DIRECTORIES true
  RELATIVE "${SRC_DIR}"
  "${SRC_DIR}/*"
)

set(_curr_src_rel_filepaths)

#REM: Copy files and create directories.
foreach(_src_rel_path IN LISTS _src_rel_paths)
  set(_src_abs_path "${SRC_DIR}/${_src_rel_path}")
  set(_dst_abs_path "${DST_DIR}/${_src_rel_path}")

  if(IS_DIRECTORY "${_src_abs_path}")
    continue()
  else()
    set(_src_abs_filepath "${_src_abs_path}")
    set(_dst_abs_filepath "${_dst_abs_path}")
    set(_src_rel_filepath "${_src_rel_path}")

    get_filename_component(_src_rel_dir 
      "${_src_rel_filepath}" DIRECTORY)
    if(_src_rel_dir)
      file(MAKE_DIRECTORY "${DST_DIR}/${_src_rel_dir}")
    endif()

    list(APPEND _curr_src_rel_filepaths "${_src_rel_filepath}")

    execute_process(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_src_abs_filepath}" "${_dst_abs_filepath}"
      RESULT_VARIABLE _copy_result
    )

    if(NOT _copy_result EQUAL 0)
      message(FATAL_ERROR "Failed to copy ${_src_abs_filepath} -> ${_dst_abs_filepath}")
    endif()
  endif()
endforeach()

#REM: Remove stale files from destination.
#REM: pattern paths: relative filepaths & directories/folders
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

#REM: Checking the dst. Remove empty directories left after deletion.
set(_is_remove TRUE)
while(_is_remove)
  set(_is_remove FALSE)

  #REM: pattern paths: relative filepaths & directories/folders
  file(GLOB_RECURSE _dst_rel_paths
    LIST_DIRECTORIES true
    RELATIVE "${DST_DIR}"
    "${DST_DIR}/*"
  )

  foreach(_dst_rel_path IN LISTS _dst_rel_paths)
    set(_dst_abs_path "${DST_DIR}/${_dst_rel_path}")

    #REM: Skip if not directory (folder)
    if(NOT IS_DIRECTORY "${_dst_abs_path}")
      continue()
    endif()

    file(GLOB _dst_abs_subpath_pattern 
      "${_dst_abs_path}/*")

    if(NOT _dst_abs_subpath_pattern)
      message(STATUS "Removing empty directory: ${_dst_abs_path}")
      file(REMOVE_RECURSE "${_dst_abs_path}")
      set(_is_remove TRUE)
    endif()
  endforeach()
endwhile()

message(STATUS "Synchronization copied paths complete.")