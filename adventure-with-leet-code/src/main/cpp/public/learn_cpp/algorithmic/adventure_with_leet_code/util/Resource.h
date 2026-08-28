#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_UTIL
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_UTIL

#include <string>
#include <filesystem>
#include "learn_cpp/algorithmic/adventure_with_leet_code/export.h"

namespace learn_cpp::algorithmic::adventure_with_leet_code::util {

  class LCXXA_AWLEETCODE_API Resource {

    public: static std::string get_exec_parent_dir();

    public: static std::filesystem::path get_template_resource_dir();

    //REM: [TODO]
    public: static std::string get_persistent_resource_dir();
    //REM: [TODO]
    public: static std::string get_temporary_resource_dir();

    /**
     * @brief 
     * 
     * @param target_filepath
     * @param required_root_dir
     * 
     * @return bool
     */
    public: static bool validate_path(
      std::filesystem::path const & target_filepath,
      std::filesystem::path const & required_root_dir 
    );
  };

  #if defined(_WIN32)
  # define PATH_SEPARATOR '\\'
  # define LIST_PATH_SEPARATOR ';'
  #else
  # define PATH_SEPARATOR '/'
  # define LIST_PATH_SEPARATOR ':'
  #endif
}

#endif