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
#include "../../include/info/dynamite/DynamicFunction.hpp"
#include "../../include/info/dynamite/exception/NoSuchFunction.hpp"

BOOST_AUTO_TEST_SUITE(DynamicLibraryTest)
using namespace std::string_literals;
using namespace info::dynamite;

BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withDefaultPrefix) {
       DynamicLibrary dyn{ "dummy" };

       BOOST_CHECK_EQUAL(dyn.winName(), "libdummy.dll");
       BOOST_CHECK_EQUAL(dyn.osxName(), "libdummy.dylib");
       BOOST_CHECK_EQUAL(dyn.elfName(), "libdummy.so");
}

BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withExplicitTruePrefix) {
       DynamicLibrary dyn{ "dummy", true };

       BOOST_CHECK_EQUAL(dyn.winName(), "libdummy.dll");
       BOOST_CHECK_EQUAL(dyn.osxName(), "libdummy.dylib");
       BOOST_CHECK_EQUAL(dyn.elfName(), "libdummy.so");
}

  BOOST_AUTO_TEST_CASE(PlatformDependentNameFunctions_shouldAlwaysReturnCorrectName_withFalsePrefix) {
         DynamicLibrary dyn{ "dummy", false };

         BOOST_CHECK_EQUAL(dyn.winName(), "dummy.dll");
         BOOST_CHECK_EQUAL(dyn.osxName(), "dummy.dylib");
         BOOST_CHECK_EQUAL(dyn.elfName(), "dummy.so");
  }

  BOOST_AUTO_TEST_CASE(ShouldReturnNamePlatformDependently_withPrefix) {
         DynamicLibrary dyn{ "dummy" };
#ifdef _WIN32
         BOOST_CHECK_EQUAL(dyn.name(), "libdummy.dll");
#elif defined(__APPLE__)
         BOOST_CHECK_EQUAL(dyn.name(), "libdummy.dylib");
#else
         BOOST_CHECK_EQUAL(dyn.name(), "libdummy.so");
#endif
  }

  BOOST_AUTO_TEST_CASE(ShouldReturnNamePlatformDependently_withoutPrefix) {
         DynamicLibrary dyn{ "dummy", false };

#ifdef _WIN32
         BOOST_CHECK_EQUAL(dyn.name(), "dummy.dll");
#elif defined(__APPLE__)
         BOOST_CHECK_EQUAL(dyn.name(), "dummy.dylib");
#else
         BOOST_CHECK_EQUAL(dyn.name(), "dummy.so");
#endif
  }

  BOOST_AUTO_TEST_CASE(Functions_shouldReturnCorrectListOfFunctions) {
      DynamicLibrary dyn{ "dummy" };

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

BOOST_AUTO_TEST_CASE(Demangled_shouldReturnCorrectListOfFunctions) {
       DynamicLibrary dyn{ "dummy" };

       auto funs = dyn.demangled();
       auto exp = std::vector{
           "param_sqr(int*, int)"s,
                  "square(int)"s
       };

       std::sort(funs.begin(), funs.end()); // for it is not necessarily in alphabetical order

       BOOST_CHECK_EQUAL(funs.size(), exp.size());
       BOOST_CHECK_EQUAL_COLLECTIONS(
       funs.begin(), funs.end(),
       exp.begin(), exp.end()
       );
}

BOOST_AUTO_TEST_CASE(getFunction_shouldReturnDynamicFunction) {
       DynamicLibrary dyn{ "dummy" };

       const DynamicFunction& dynamicFunction = dyn.getFunction("square(int)");

       BOOST_CHECK_NE(dynamicFunction.handle(), nullptr);
       BOOST_CHECK_EQUAL(dynamicFunction.name(), "square(int)");
}

BOOST_AUTO_TEST_CASE(getFunction_shouldThrow_ifFunctionCannotBeFound) {
       DynamicLibrary dyn{ "dummy" };
       std::string fname{ "absurdity(int)" };

       try {
           auto _ = dyn.getFunction(fname);
       } catch (no_such_function& e) {
           BOOST_CHECK_EQUAL(e.what(), "Requested function `" + fname + "` not found.");
           return;
       } catch (std::exception& e) {
           std::cerr << e.what() << std::endl;
           BOOST_FAIL("Unexpected type of exception thrown.");
       }

       BOOST_FAIL("Expected exception not thrown.");
}

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop

#pragma clang diagnostic pop
