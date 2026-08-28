#include <string>
#include <stdexcept>
#include <vector>
#include <exception>

#if defined(_WIN32)
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
# endif
# ifndef NOMINMAX
#   define NOMINMAX
# endif
# include <windows.h>
#elif defined(__linux__)
# include <unistd.h>
#elif defined(__APPLE__)
# include <mach-o/dyld.h>
#endif

#ifndef LCXXA_AWLEETCODE_REZ_DIR
# define LCXXA_AWLEETCODE_REZ_DIR "resources"
#endif

#include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"

namespace learn_cpp::algorithmic::adventure_with_leet_code::util
{

  std::string Resource::get_exec_parent_dir()
  {
    std::string filepath;
    std::size_t idx = std::string::npos;

  #if defined(_WIN32)
    //REM: Use wide characters (wchar_t) to bypass the ANSI MAX_PATH limit natively
    std::vector<wchar_t> wbuff(1024);
    while (true)
    {
      DWORD len = GetModuleFileNameW(
        NULL,
        wbuff.data(),
        static_cast<DWORD>(wbuff.size())
      );

      if (len == 0)
      {
        throw std::runtime_error("Win32 GetModuleFileNameW failed completely.");
      }

      if (len < wbuff.size())
      {
        //REM: If the acquired len is less than to the said buff size, then we did acquired the correct full raw bytes path.
        std::wstring wpath(wbuff.data(), len);

        //REM: Handle the \\?\ prefix if Windows automatically inserted it for a long path
        if (wpath.rfind(L"\\\\?\\", 0) == 0)
        {
          wpath = wpath.substr(4);
        }

        //REM: Convert safely to a UTF-8 encoded std::string
        int size_needed = WideCharToMultiByte(
          CP_UTF8,
          0,
          wpath.c_str(),
          static_cast<int>(wpath.length()),
          NULL,
          0,
          NULL,
          NULL
        );

        if (size_needed > 0)
        {
          filepath.resize(static_cast<std::size_t>(size_needed));
          WideCharToMultiByte(
            CP_UTF8,
            0,
            wpath.c_str(),
            static_cast<int>(wpath.length()),
            &filepath[0],
            size_needed,
            NULL,
            NULL
          );
        }
        break;
      }
      wbuff.resize(wbuff.size() * 2);
    }
    idx = filepath.find_last_of("\\/");

  #elif defined(__linux__)
    //REM: Symlinks in procfs report a size of 0, so we must dynamically guess and grow
    std::vector<char> buff(1024);
    while (true)
    {
      //REM: readlink does not append a null terminator
      ssize_t len = readlink("/proc/self/exe", buff.data(), buff.size());
      if (len == -1)
      {
        throw std::runtime_error("Linux readlink failed completely.");
      }
      if (static_cast<std::size_t>(len) < buff.size())
      {
        //REM: If the acquired len is less than to the said buff size (capacity), then we did acquired the correct full raw bytes path.
        filepath.assign(buff.data(), static_cast<std::size_t>(len));
        break;
      }
      buff.resize(buff.size() * 2);
    }
    idx = filepath.find_last_of("/");

  #elif defined(__APPLE__)
    unsigned int size = 0;
    //REM: Calling with nullptr returns -1 but populates 'size' with the exact required capacity
    _NSGetExecutablePath(nullptr, &size);

    std::vector<char> buff(size);
    if (_NSGetExecutablePath(buff.data(), &size) == 0)
    {
      filepath.assign(buff.data());
    }
    else
    {
      throw std::runtime_error("macOS _NSGetExecutablePath failed.");
    }
    idx = filepath.find_last_of("/");
  #endif

    if (idx != std::string::npos)
    {
      return filepath.substr(0, idx);
    }

    return ".";
  }

  std::filesystem::path Resource::get_template_resource_dir() {
    //REM: Get the baseline directory where the executable file lives
    std::filesystem::path base_binary_dir = Resource::get_exec_parent_dir();

    //REM: Read the macro string passed by your CMake script
    std::filesystem::path relative_rez_path(LCXXA_AWLEETCODE_REZ_DIR);

    //REM: Combine them natively
    std::filesystem::path dynamic_resolved_path = base_binary_dir / relative_rez_path;

    //REM: Determine the correct allowed sandbox root based on the platform policy
  #if defined(WIN32) || defined(_WIN32)
    //REM: Windows expects resources right next to or inside the binary folder
    std::filesystem::path allowed_root = base_binary_dir;
  #else
      //REM: Linux expects resources to back out into a shared folder (e.g., bin/../share/)
      //REM: We expand the sandbox boundary to the common parent directory of the binary folder
    std::filesystem::path allowed_root = base_binary_dir.parent_path();
  #endif

      //REM: Validate against the appropriate platform sandbox root
    if (!Resource::validate_path(dynamic_resolved_path, allowed_root))
    {
      throw std::runtime_error("Resource Violation: Resolved path lies outside the allowed sandbox root boundary!");
    }

    //REM: Return a clean, standardized canonical path format
    return dynamic_resolved_path.lexically_normal();
  }

  // void Resource::validate_path(
  //   std::filesystem::path const& target_filepath,
  //   std::filesystem::path const& required_root_dir
  // ) {
  //   std::string target = target_filepath.string();
  //   std::string root = required_root_dir.string();

  //   if (target.find(root) != 0)
  //     throw std::runtime_error("Security Exception: Directory traversal violation blocked outside system control.");
  // }

  /*
  bool Resource::validate_path(
    std::filesystem::path const & target_filepath,
    std::filesystem::path const & required_root_dir
  ) {

    std::error_code ec;

    //REM: Optional but recommended: reject absolute user input explicitly
    // if (target_filepath.is_absolute())
    //     return false;

    //REM: It resolve paths (resolve path traversal, symlinks final location, normalized paths)
    std::filesystem::path canonical_root
      = std::filesystem::weakly_canonical(
          required_root_dir, ec);

    if (ec)
      return false;

    if (!std::filesystem::is_directory(canonical_root, ec) || ec)
      return false;

    std::filesystem::path combined
      = target_filepath.is_absolute()
        ? target_filepath
        : required_root_dir / target_filepath;

    //REM: It resolve paths (resolve path traversal, symlinks final location, normalized paths)
    std::filesystem::path secure_target
      = std::filesystem::weakly_canonical(combined, ec);

    if (ec)
      return false;

    //REM: canonical_root ---> /root/path/
    //REM: secure_target ---> /root/path/to/secure/target.ext
    //REM: ===
    //REM: pair.first (fs::path::iter) ---> canonical_root.end() [UB address]
    //REM: pari.second (fs::path::iter) ---> "to"
    std::pair<
      std::filesystem::path::iterator, std::filesystem::path::iterator
    > result = std::mismatch(
        canonical_root.begin(),
        canonical_root.end(),
        secure_target.begin(),
        secure_target.end()
      );

    return result.first == canonical_root.end();
  }
  */

  bool Resource::validate_path(
    std::filesystem::path const& target_filepath,
    std::filesystem::path const& required_root_dir
  ) {
    std::error_code ec;

    //REM: 1. Resolve the root directory cleanly
    std::filesystem::path canonical_root
      = std::filesystem::weakly_canonical(required_root_dir, ec);
    if (ec || !std::filesystem::is_directory(canonical_root, ec))
    {
      return false;
    }

    //REM: 2. Combine target_filepath explicitly with the ALREADY canonicalized root
    std::filesystem::path combined = target_filepath.is_absolute()
      ? target_filepath
      : canonical_root / target_filepath;

    //REM: 3. Resolve the final target location
    std::filesystem::path secure_target
      = std::filesystem::weakly_canonical(combined, ec);
    if (ec)
    {
      return false;
    }

  //REM: 4. Handle OS Case Sensitivity & Normalization Differences
  #if defined(WIN32) || defined(_WIN32)
    //REM: On Windows, convert both canonical paths to a safe, 
    //REM: uniform lowercase string format (because of std::mismatch). 
    std::wstring root_str = canonical_root.wstring();
    std::wstring target_str = secure_target.wstring();
    std::transform(
      root_str.begin(), root_str.end(), root_str.begin(), ::towlower);
    std::transform(
      target_str.begin(), target_str.end(), target_str.begin(), ::towlower);

    //REM: Turning them back into paths for iterator verification.
    std::filesystem::path final_root(root_str);
    std::filesystem::path final_target(target_str);
  #else
    //REM: On Linux, case matters natively. We can pass the exact values through directly.
    std::filesystem::path const& final_root = canonical_root;
    std::filesystem::path const& final_target = secure_target;
  #endif

    auto result = std::mismatch(
      final_root.begin(), final_root.end(),
      final_target.begin(), final_target.end()
    );

    //REM: If result.first reached the end of the root path, the target is safely inside!
    return result.first == final_root.end();
  }

}
