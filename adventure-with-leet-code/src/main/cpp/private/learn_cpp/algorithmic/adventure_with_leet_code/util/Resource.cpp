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

#include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"

namespace learn_cpp::algorithmic::adventure_with_leet_code::util
{

  std::string Resource::get_exec_parent_filepath()
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

  void Resource::validate_filepath(
    std::filesystem::path const & target_filepath,
    std::filesystem::path const & required_root_filepath
  ) {
    std::string target = target_filepath.string();
    std::string root = required_root_filepath.string();

    if(target.find(root) != 0)
      throw std::runtime_error("Security Exception: Directory traversal violation blocked outside system control.");
  }
}
