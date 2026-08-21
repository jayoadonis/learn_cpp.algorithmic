
#include <cstdio>
#include <catch2/catch_session.hpp>
#include "unit/resource.h"
#include "integration/resource.h"

int main(int arg_c, char* arg_v[]) {

  //REM: Optional: Place global setup here (e.g., environment mocks, logger initialization)

  int result = Catch::Session().run(arg_c, arg_v);

  //REM: Optional: Place global teardown here

  std::fprintf(stdout, "%s\n", "Test Done.");

  return result;
}


// #include <cstdio>
// #include <cassert>
// #include <string>
// #include "./util/TestType.h"
// #include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"
// #include "learn_cpp/algorithmic/adventure_with_leet_code/easy/ch_000_001_two_sum.h"
// #include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"

// int main(int arg_c, char** arg_v) {

//   using namespace learn_cpp::algorithmic;

//   std::fprintf(stdout, "%s\n", (arg_v[1] ? arg_v[1] : "<npos>"));

//   adventure_with_leet_code::easy::Solution solution;

//   assert(solution.two_sum({ 10,3,7,9 }, 10)[0] == 1 && "Expected index (1)");
//   assert(solution.two_sum({ 10,3,7,9 }, 10)[1] == 2 && "Expected index (2)");

//   std::vector<std::size_t> two_indices
//     = solution.two_sum_002({ 10,3,7,9 }, 10);

//   assert(two_indices[0] == 1);
//   assert(two_indices[1] == 2);

//   adventure_with_leet_code::test::util::TestType test_type
//     = adventure_with_leet_code::test::util::parse_to_test_type(
//       arg_v[1] ? arg_v[1] : ""
//     );

//   std::pair<std::size_t, std::size_t> two_indices_003
//     = solution.two_sum_003<static_cast<std::size_t>(4)>({ 2,4,2,5 }, 9);

//   std::pair<std::size_t, std::size_t> two_indices_003_ii
//     = solution.two_sum_003<static_cast<std::size_t>(4)>({ 2,4,2,5 }, 9);

//   assert(two_indices_003.first == 1);
//   assert(two_indices_003.second == 3);

//   assert(two_indices_003_ii.first == 1);
//   assert(two_indices_003_ii.second == 3);

//   std::string exec_parent_filepath = adventure_with_leet_code::util::
//     Resource::get_exec_parent_filepath();

//   std::string data_test_sqlite 
//     = exec_parent_filepath + PATH_SEPARATOR + "resources" + PATH_SEPARATOR + "data.test.db";

//   adventure_with_leet_code::util::Resource::validate_filepath(
//     data_test_sqlite,
//     exec_parent_filepath
//   );

//   std::fprintf(stdout, "<<< %s\n", exec_parent_filepath.c_str());

//   std::fprintf(stdout, "<<< %s\n", data_test_sqlite.c_str());

//   std::fprintf(stdout, "::: %zu\n", static_cast<std::size_t>(test_type));
//   std::fprintf(stdout, "::: %s\n", "Testing done.");
//   return 0;
// }