

#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_INTEGRATION_RESOURCE_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_INTEGRATION_RESOURCE_H

#include <catch2/catch_test_macros.hpp>
#include <string>

#include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"

using namespace learn_cpp::algorithmic;

TEST_CASE("testing resourcex", "[integration]") {

  SECTION("check exec parent path") {

    std::string exec_parent_filepath 
      = adventure_with_leet_code::util::Resource::
        get_exec_parent_dir();

    REQUIRE( !exec_parent_filepath.empty() );

  }
}


TEST_CASE("testing goldx", "[integration]") {

  SECTION("check exec parent path") {

    std::string exec_parent_filepath 
      = adventure_with_leet_code::util::Resource::
        get_exec_parent_dir();

    REQUIRE( !exec_parent_filepath.empty() );

  }
}

#endif