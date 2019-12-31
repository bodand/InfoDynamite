//
// Created by tudom on 2019-12-28.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStaticInspection"
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <boost/test/included/unit_test.hpp>

#include <liblucent/lucent.hpp>

BOOST_AUTO_TEST_SUITE(Demangler)
  using namespace liblucent;

  BOOST_AUTO_TEST_CASE(Demangle_shouldReturnSameString_ifNotMangledNameIsGiven) {
      std::string inp{"SomeNonMangledName"};
      auto ret = Demangle(inp);

      BOOST_CHECK_EQUAL(ret, inp);
  }

  BOOST_AUTO_TEST_CASE(Demangle_shouldReturnCorrectlyDemangledName) {
      std::string inp{
#ifdef LIBLUCENT_MSABI_MANGING_SCHEME
             "??$func@H@@YAXHPEAH$$QEAHP6AXXZA6AHH@Z@Z"
#else
             "_Z2iiiOPiKRKiPFviE"
#endif
      };

      BOOST_CHECK_EQUAL(Demangle(inp), "ii(int, int*&&, int const& const, void (*)(int))");
  }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop

#pragma clang diagnostic pop
