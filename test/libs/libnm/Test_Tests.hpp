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

BOOST_AUTO_TEST_SUITE(Trivial)

  BOOST_AUTO_TEST_CASE(FrameworkTest) {
      BOOST_CHECK_MESSAGE(true, "Your Boost is properly installed");
  }

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop

#pragma clang diagnostic pop
