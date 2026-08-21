#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_UTIL_TEST_TYPE_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_UTIL_TEST_TYPE_H

#include <cstddef>
#include <string_view>

/**
 * @brief Primarilly use for raw/vanilla test suite with assert
 * 
 */
namespace learn_cpp::algorithmic::adventure_with_leet_code::test::util {

  enum class TestType : std::size_t;

  TestType parse_to_test_type(std::string_view const & sv);
}

#endif
