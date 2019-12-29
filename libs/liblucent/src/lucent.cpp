//
// Created by tudom on 2019-12-28.
//

#include "include.hpp"
#include LIBLUCENT_INCLUDE_HEADER(lucent.hpp)

bool liblucent::detail::balanced_parens(std::string_view str) {
    unsigned found{0};
    for (const auto& ch : str) {
        switch (ch) {
            case '(':
                found++;
                break;
            case ')':
                found--;
                break;
            default:
                break;
        }
    }
    return found == 0;
}
