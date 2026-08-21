#[[
Copies filepaths to a target's runtime directory (destination) and removes stale filepaths
that were previously copied, based on a manifest file.

Inputs:
  SRC_FILES     - source of list of absolute paths
  DST_DIR       - destination directory
  MANIFEST_FILE - it is filepath storing the said source for absolute paths of previously copied paths

If MANIFEST_FILE is not defined or empty, the script only copies files
and does not delete anything.


#REM: such as;
SRC_FILES `path/to/src/file_i;path/to/src/file_ii`
DST_DIR `path/to/dst_dir`
MANIFEST `path/to/.sync.$<CONFIG>.manifest`

(copied files into dst)
  `path/to/dst_dir/file_i`
  `path/to/dst_dir/file_ii`
]]

message(STATUS "Synchronizing filepaths")
message(STATUS "  SRC_FILES:  [${SRC_FILES}]")
message(STATUS "  DST_DIR:    '${DST_DIR}'")

if(NOT DEFINED DST_DIR)
  message(FATAL_ERROR "DST_DIR is required")
endif()

if(NOT DEFINED SRC_FILES)
  set(SRC_FILES "")
endif()

file(MAKE_DIRECTORY "${DST_DIR}")

set(_curr_dst_filepaths)

foreach(_src_filepath IN LISTS SRC_FILES)
  if(NOT EXISTS "${_src_filepath}")
    message(WARNING "Source filepath does not exist: ${_src_filepath}")
    continue()
  endif()

  get_filename_component(_fname "${_src_filepath}" NAME)
  set(_dst_filepath "${DST_DIR}/${_fname}")

  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_src_filepath}" "${_dst_filepath}"
    RESULT_VARIABLE _copy_result
  )

  if(NOT _copy_result EQUAL 0)
    message(FATAL_ERROR "Failed to copy ${_src_filepath} -> ${_dst_filepath}")
  endif()

  list(APPEND _curr_dst_filepaths "${_dst_filepath}")
endforeach()

#REM: Remove stale filepaths tracked by the previous manifest.
if(DEFINED MANIFEST_FILE AND NOT "${MANIFEST_FILE}" STREQUAL "")
  if(EXISTS "${MANIFEST_FILE}")
    file(STRINGS "${MANIFEST_FILE}" _old_manifest)

    foreach(_old_dst IN LISTS _old_manifest)
      list(FIND _curr_dst_filepaths "${_old_dst}" _idx)
      if(_idx EQUAL -1)
        if(EXISTS "${_old_dst}")
          message(STATUS "Removing stale filepaths: ${_old_dst}")
          file(REMOVE "${_old_dst}")
        endif()
      endif()
    endforeach()
  endif()

  #REM: Write new manifest.
  file(WRITE "${MANIFEST_FILE}" "")
  foreach(_dst_filepath IN LISTS _curr_dst_filepaths)
    file(APPEND "${MANIFEST_FILE}" "${_dst_filepath}\n")
  endforeach()
else()
  message(WARNING "MANIFEST_FILE is undefined.")
endif()

message(STATUS "Synchronization copied filepaths complete.")