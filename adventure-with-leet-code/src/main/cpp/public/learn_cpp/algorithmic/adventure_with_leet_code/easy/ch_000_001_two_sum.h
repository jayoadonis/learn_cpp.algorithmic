#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EASY_CH_000_001_TWO_SUM_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EASY_CH_000_001_TWO_SUM_H

#include <array>
#include <cstddef>
#include <vector>
#include "learn_cpp/algorithmic/adventure_with_leet_code/export.h"

namespace learn_cpp::algorithmic::adventure_with_leet_code::easy {

  class LCXXA_AWLEETCODE_API Solution {

    //REM: [TODO_API_COMMENT]
    public: std::vector<std::size_t> two_sum(
      std::vector<signed long long> const& nums,
      signed long long target
    );

    //REM: [TODO_API_COMMENT]
    public: std::vector<std::size_t> two_sum_002(
      std::vector<signed long long> const& nums,
      signed long long target
    );

    public: 
    template<std::size_t N> 
    std::pair<std::size_t, std::size_t> two_sum_003(
      std::array<signed long long, N> const& arr, 
      signed long long target
    );
  };
}

#include "./ch_000_001_two_sum.tpp"

#endif