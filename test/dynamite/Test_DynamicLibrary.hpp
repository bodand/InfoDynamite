//
// Created by bodand on 2019-12-22.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStaticInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <boost/test/included/unit_test.hpp>

#include "../../include/info/dynamite/DynamicLibrary.hpp"

BOOST_AUTO_TEST_SUITE(DynamicLibraryTest)
  using namespace std::string_literals;
  using namespace info::dynamite;

  BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withDefaultPrefix) {
      DynamicLibrary dyn{"dynamite"};

      BOOST_CHECK_EQUAL(dyn.winName(), "libdynamite.dll");
      BOOST_CHECK_EQUAL(dyn.osxName(), "libdynamite.dylib");
      BOOST_CHECK_EQUAL(dyn.elfName(), "libdynamite.so");
  }

  BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withExplicitTruePrefix) {
      DynamicLibrary dyn{"dynamite", true};

      BOOST_CHECK_EQUAL(dyn.winName(), "libdynamite.dll");
      BOOST_CHECK_EQUAL(dyn.osxName(), "libdynamite.dylib");
      BOOST_CHECK_EQUAL(dyn.elfName(), "libdynamite.so");
  }

  BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withFalsePrefix) {
      DynamicLibrary dyn{"dynamite", false};

      BOOST_CHECK_EQUAL(dyn.winName(), "dynamite.dll");
      BOOST_CHECK_EQUAL(dyn.osxName(), "dynamite.dylib");
      BOOST_CHECK_EQUAL(dyn.elfName(), "dynamite.so");
  }

  BOOST_AUTO_TEST_CASE(ShouldReturnNamePlatformDependently_withPrefix) {
      DynamicLibrary dyn{"dynamite"};
#ifdef _WIN32
      BOOST_CHECK_EQUAL(dyn.name(), "libdynamite.dll");
#elif defined(__APPLE__)
      BOOST_CHECK_EQUAL(dyn.name(), "libdynamite.dylib");
#else
      BOOST_CHECK_EQUAL(dyn.name(), "libdynamite.so");
#endif
  }

  BOOST_AUTO_TEST_CASE(ShouldReturnNamePlatformDependently_withoutPrefix) {
      DynamicLibrary dyn{"dynamite", false};
#ifdef _WIN32
      BOOST_CHECK_EQUAL(dyn.name(), "dynamite.dll");
#elif defined(__APPLE__)
      BOOST_CHECK_EQUAL(dyn.name(), "dynamite.dylib");
#else
      BOOST_CHECK_EQUAL(dyn.name(), "dynamite.so");
#endif
  }

  BOOST_AUTO_TEST_CASE(Functions_shouldReturnCorrectListOfFunctions) {
      DynamicLibrary dyn{"dummy"};

      auto funs = dyn.functions();
      auto exp = std::vector{
             "_Z6squarei"s,
             "_Z9param_sqrPii"s
      };

      std::sort(funs.begin(), funs.end()); // for it is not necessarily in alphabetical order

      BOOST_CHECK_EQUAL(funs.size(), exp.size());
      BOOST_CHECK_EQUAL_COLLECTIONS(
             funs.begin(), funs.end(),
             exp.begin(), exp.end()
      );
  }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop

#pragma clang diagnostic pop
