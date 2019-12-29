//
// Created by tudom on 2019-12-28.
//

#include "../include.hpp"
#include LIBLUCENT_INCLUDE_HEADER_F(lucent.hpp)

#include <windows.h>
#include <dbghelp.h>
#include <stack>

std::string liblucent::Demangle(std::string_view name) {
    using detail::balanced_parens;

    std::string ret{};
    ret.reserve(5);

    do {
        if (!UnDecorateSymbolName(name.data(), ret.data(), ret.size(), UNDNAME_COMPLETE)) {
            return std::string{name};
        }
    } while (!(ret.back() == ')' && balanced_parens(ret)) && (ret.reserve(ret.size() * 2), true));

    ret.shrink_to_fit();
    return ret;
}
