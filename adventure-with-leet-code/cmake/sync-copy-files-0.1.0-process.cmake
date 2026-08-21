#[[USAGE:

#REM: Windows dll
add_custom_command(TARGET 
  ${_PROJECT_TARGET_TEST_NAME} 
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
    "-DSRC_FILES=$<TARGET_RUNTIME_DLLS:${_PROJECT_TARGET_TEST_NAME}>"
    "-DDST_DIR=$<TARGET_FILE_DIR:${_PROJECT_TARGET_TEST_NAME}>"
    -P "${PROJECT_SOURCE_DIR}/cmake/copy_files.process.cmake"
  VERBATIM
  COMMENT "::: Windows runtime dlls trying to copy relative to executable natively"
)

#REM: such as;
SRC_FILES `path/to/src/file_i;path/to/src/file_ii`
DST_DIR `path/to/dst_dir`

(copied files into dst)
  `path/to/dst_dir/file_i`
  `path/to/dst_dir/file_ii`
]]

message(STATUS "Synchronizing filepaths")
message(STATUS "  SRC_FILES:  [${SRC_FILES}]")
message(STATUS "  DST_DIR:    '${DST_DIR}'")

if(SRC_FILES)
  file(MAKE_DIRECTORY "${DST_DIR}")

  foreach(_src IN LISTS SRC_FILES)
    execute_process(
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_src}" "${DST_DIR}"
      RESULT_VARIABLE _copy_result
    )

    if(NOT _copy_result EQUAL 0)
      message(FATAL_ERROR
        "Failed to copy: ${_src} -> ${DST_DIR} (exit code ${_copy_result})"
      )
    endif()
  endforeach()
endif()

message(STATUS "Synchronization copied filepaths complete.")