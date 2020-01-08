//
// Created by tudom on 2019-12-31.
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

BOOST_AUTO_TEST_SUITE(DynamicFunctionTest)
using namespace std::string_literals;
using namespace info::dynamite;

BOOST_AUTO_TEST_CASE(ShouldBeCallableWithRequiredTypes) {
       DynamicLibrary dyn{ "dummy" };
       auto f = dyn.getFunction("param_sqr(int*, int)");

       int v = 2;
       int res = 0;

       BOOST_REQUIRE_NE(f.handle(), nullptr);

       f(&res, v);

       BOOST_CHECK_EQUAL(v, 2);
       BOOST_CHECK_EQUAL(res, 4);
}

BOOST_AUTO_TEST_CASE(ShouldBeCalledWithExplicitCallFunctionWithRequiredTypes) {
       DynamicLibrary dyn{ "dummy" };
       auto f = dyn.getFunction("param_sqr(int*, int)");

       int v = 2;
       int res = 0;

       BOOST_REQUIRE_EQUAL(res, 0);
       BOOST_REQUIRE_EQUAL(v, 2);
       BOOST_REQUIRE_NE(f.handle(), nullptr);

       f.call(&res, v);

       BOOST_CHECK_EQUAL(v, 2);
       BOOST_CHECK_EQUAL(res, 4);
}

BOOST_AUTO_TEST_CASE(ShouldReturnCorrectValueWithCallReturn) {
       DynamicLibrary dyn{ "dummy" };
       auto f = dyn.getFunction("square(int)");

       int v = 2;

       BOOST_REQUIRE_EQUAL(v, 2);
       BOOST_REQUIRE_NE(f.handle(), nullptr);

       BOOST_CHECK_EQUAL(v, 2);
       BOOST_CHECK_EQUAL(f.callReturn<int>(v), 4);
}

BOOST_AUTO_TEST_SUITE_END()

#pragma clang diagnostic pop

#pragma clang diagnostic pop
