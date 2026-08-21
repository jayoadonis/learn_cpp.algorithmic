#include "learn_cpp/algorithmic/adventure_with_leet_code/easy/ch_000_001_two_sum.h"

#include <algorithm>
#include <unordered_map>

/*
 * O(NlogN) == N * (log base-2 N == depth)
 */
namespace learn_cpp::algorithmic::adventure_with_leet_code::easy {

  /**
   * @brief 
   * O(NlogN) Time Complexity
   * O(N) Space Complexity
   * 
   * @param nums 
   * @param target 
   * @return std::vector<std::size_t> - two indices
   */
  std::vector<std::size_t> Solution::two_sum(
    std::vector<signed long long> const & nums,
    signed long long target
  ) {

    std::vector<std::pair<signed long long, std::size_t>> value_index_list;
    value_index_list.reserve(nums.size());

    //REM: O(N) time complexity
    //REM: O(N) space complexity
    for(std::size_t i = 0; i < nums.size(); ++i) {
      value_index_list.push_back({nums[i], i});
    }

    //REM: O(NlogN) time complexity
    //REM: O(1) * O(logN) space complexity
    std::sort(value_index_list.begin(), value_index_list.end(),
      [](std::pair<signed long long, std::size_t> const & x,
        std::pair<signed long long, std::size_t> const & y
      ) noexcept -> bool {
        if(x.first != y.first)
          return x.first < y.first;
        return x.second < y.second;
      }
    );

    std::size_t left = 0;
    std::size_t right = value_index_list.size() - 1;

    //REM: O(N) time complexity
    //REM: O(1) space complexity
    while(left < right) {
      signed long long current_sum = 
        value_index_list[left].first + value_index_list[right].first;
      if(current_sum == target) {
        return {value_index_list[left].second, value_index_list[right].second};
      }
      else if(current_sum < target){
        ++left;
      }
      else {
        --right;
      }
    }

    return {};
  }

  /**
   * @brief
   * O(N) Time Complexity
   * O(N) Space Complexity
   * 
   * @param nums 
   * @param target 
   * @return std::vector<std::size_t> - two indices
   */
  std::vector<std::size_t> Solution::two_sum_002(
    std::vector<signed long long> const & nums,
    signed long long target
  ) {

    std::unordered_map<signed long long, std::size_t> seen;
    seen.reserve(nums.size());

    //REM: O(N) tc
    for(std::size_t i = 0; i < nums.size(); ++i) {
      signed long long complement = target - nums[i];
      if(seen.find(complement) != seen.end())
        return {seen[complement], i};
      //REM: O(N) sc
      seen[nums[i]] = i;
    }

    return {};
  }
}