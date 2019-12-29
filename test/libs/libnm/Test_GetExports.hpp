//
// Created by bodand on 2019-12-22.
//

#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStaticInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <boost/test/included/unit_test.hpp>
#include "../../../libs/libnm/include/libnm/nm.hpp"
#include "../../../libs/libnm/include/libnm/FileNotObject.hpp"
#include "../../../libs/libnm/include/libnm/FileDoesNotExist.hpp"

BOOST_AUTO_TEST_SUITE(libnm_test)
  using namespace libnm;

  BOOST_AUTO_TEST_CASE(GetExports_shouldThrow_ifFileIsNotSharedObject) {
      std::string file{"Makefile"};
      try {
          auto _ = GetExports(file);
      } catch (file_not_object& e) {
          BOOST_CHECK_MESSAGE(true, "Exception thrown where expected.");
          BOOST_CHECK_EQUAL(std::string{e.what()},
                            "File `" + file + "' is not a shared object.");
          return;
      }
      BOOST_FAIL("Exception not thrown where one is expected.");
  }

  BOOST_AUTO_TEST_CASE(GetExports_shouldThrow_ifFileDoesNotExists) {
      std::string file{"Cocaine"};
      try {
          auto _ = GetExports(file);
      } catch (file_does_not_exist& e) {
          BOOST_CHECK_MESSAGE(true, "Exception thrown where expected.");
          BOOST_CHECK_EQUAL(std::string{e.what()},
                            "File `" + file + "' does not exist.");
          return;
      }
      BOOST_FAIL("Exception not thrown where one is expected.");
  }

  BOOST_AUTO_TEST_CASE(GetExports_shouldReturnCorrectNumberOfExports) {
      std::string file{
#ifdef WIN32
             "libdummy.dll"
#elif __APPLE__
             "libdummy.dylib"
#else
             "libdummy.so"
#endif
      };

      std::vector<std::string> exports;
      try {
          exports = GetExports(file);
      } catch (std::exception& e) {
          std::cerr << e.what() << std::endl;
          BOOST_FAIL("Unexpected exception thrown");
      }

      BOOST_CHECK_EQUAL(exports.size(), 2);
  }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop
