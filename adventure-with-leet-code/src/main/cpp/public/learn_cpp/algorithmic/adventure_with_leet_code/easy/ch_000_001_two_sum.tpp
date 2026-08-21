#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EASY_CH_000_001_TWO_SUM_TPP
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_EASY_CH_000_001_TWO_SUM_TPP

#include <cstdio>
#include <algorithm>
#include "learn_cpp/algorithmic/adventure_with_leet_code/easy/ch_000_001_two_sum.h"

namespace learn_cpp::algorithmic::adventure_with_leet_code::easy {

  //REM: O(NlogN) - TIME COMPLEXITY
  //REM: O(N)     - SPACE COMPLEXITY
  template<std::size_t N>
  std::pair<std::size_t, std::size_t> Solution::two_sum_003(
    std::array<signed long long, N> const& arr,
    signed long long target
  ) {

    struct Data {
      std::size_t key;
      signed long long value;
    };

    std::array<Data, N> data_list;

    for(std::size_t i = 0; i < N; ++i) {
      data_list[i] = Data{i, arr[i]};
    }

    std::sort(data_list.begin(), data_list.end(),
      [](Data const & x, Data const & y) -> bool {
        return x.value < y.value;
      }
    );

    std::size_t left_idx = 0;
    std::size_t right_idx = N - 1;

    while(left_idx < right_idx) {
      signed long long current_sum 
        = data_list[left_idx].value + data_list[right_idx].value;

      if(current_sum == target) {
        return {data_list[left_idx].key, data_list[right_idx].key};
      }
      else if (current_sum < target) {
        ++left_idx;
      }
      else {
        --right_idx;
      }
    }

    return {};
  }
}

#endif