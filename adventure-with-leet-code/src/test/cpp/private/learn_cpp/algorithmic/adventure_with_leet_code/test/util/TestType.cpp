#include "TestType.h"
#include <algorithm>
#include <cctype> //REM: std::tolower, std::toupper, & ...
#include <string_view>
#include <cstddef>

namespace learn_cpp::algorithmic::adventure_with_leet_code::test::util {

  namespace {
    bool case_insensitive_equal(
      std::string_view const& sv,
      std::string_view sv_2
    ) {
      if (sv.size() != sv_2.size())
        return false;

      return std::equal(
        sv.begin(), sv.end(),
        sv_2.begin(),
        [](unsigned char x, unsigned char x_2) noexcept {
          return std::tolower(x) == std::tolower(x_2);
        }
      );
    }
  }

  enum class TestType : std::size_t {
    UNKNOWN = 0,
    UNIT,
    INTEGRATION
  };

  TestType parse_to_test_type(std::string_view const& sv) {
    if (case_insensitive_equal(sv, "--unit-test"))
      return TestType::UNIT;
    if (case_insensitive_equal(sv, "--integration-test"))
      return TestType::INTEGRATION;

    return TestType::UNKNOWN;
  }
}
