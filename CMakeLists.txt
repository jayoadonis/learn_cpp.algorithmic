cmake_minimum_required(VERSION 3.24)
project(algorithmic
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX)

string(STRIP "${_ROOT_PROJECT_NAME}" _ROOT_PROJECT_NAME)
if(_ROOT_PROJECT_NAME)
  string(APPEND _ROOT_PROJECT_NAME ".${PROJECT_NAME}")
else()
  set(_ROOT_PROJECT_NAME "${PROJECT_NAME}")
endif()

add_subdirectory(adventure-with-leet-code)
