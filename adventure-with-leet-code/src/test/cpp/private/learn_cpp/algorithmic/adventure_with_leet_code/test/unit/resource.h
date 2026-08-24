

#ifndef LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_UNIT_RESOURCE_H
#define LEARN_CPP_ALGORITHMIC_ADVENTURE_WITH_LEET_CODE_TEST_UNIT_RESOURCE_H

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <filesystem>
#include <fstream>

#include "learn_cpp/algorithmic/adventure_with_leet_code/util/Resource.h"
#include "learn_cpp/algorithmic/adventure_with_leet_code/easy/func_ii.internal.h"

using namespace learn_cpp::algorithmic;

TEST_CASE("testing resource", "[unit]") {

  std::string exec_parent_filepath 
    = adventure_with_leet_code::util::Resource::
    get_exec_parent_filepath();

  SECTION("check exec parent path") {

    REQUIRE( !exec_parent_filepath.empty() );
  }

  SECTION("Check 2sum content") {
    
    #if defined(_WIN32)
    # define REZ "../bin/resources"
    #elif defined(__GNUC__) || defined(__clang__)
    # define REZ "../share/adventure-with-leet-code/resources"
    #else
    # define REZ "resources"
    #endif
    std::filesystem::path filepath 
      = adventure_with_leet_code::util::Resource::
        get_exec_parent_filepath() + "/" + REZ + "/data/2sum.test.txt";

  
    // std::fprintf(stdout, ">>><<<< %s\n", 
    //   filepath.string().c_str());

    std::fstream file_stream(filepath, 
      std::ios::in | std::ios::out);

    REQUIRE( file_stream.is_open() );

    file_stream.seekg(0, std::ios::beg); 

    std::string line;
    while(std::getline(file_stream, line)) {
      // std::fprintf(stdout, ">>><<<< %s\n", line.c_str());
      REQUIRE(line == "[data]");
      break;
    }

    file_stream.close();
  }
}


TEST_CASE("testing resource ii", "[unit]") {

  SECTION("check exec parent path") {

    std::string exec_parent_filepath 
      = adventure_with_leet_code::util::Resource::
        get_exec_parent_filepath();

    REQUIRE( !exec_parent_filepath.empty() );

  }
}

#endif