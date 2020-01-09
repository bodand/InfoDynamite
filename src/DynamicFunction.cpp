//
// Created by tudom on 2019-12-31.
//

#include "include.hpp"
#include INFO_DYNAMITE_INCLUDE(_api.hpp)
#include INFO_DYNAMITE_INCLUDE(DynamicFunction.hpp)

INFO_DYNAMITE_API
info::dynamite::DynamicFunction::DynamicFunction(AbstractFunction handle, std::string name) noexcept
       : _handle{handle},
         _name{std::move(name)} {}

INFO_DYNAMITE_API
info::dynamite::AbstractFunction&
info::dynamite::DynamicFunction::handle() noexcept {
    return _handle;
}

INFO_DYNAMITE_API
const info::dynamite::AbstractFunction&
info::dynamite::DynamicFunction::handle() const noexcept {
    return _handle;
}

INFO_DYNAMITE_API
std::string&
info::dynamite::DynamicFunction::name() noexcept {
    return _name;
}

INFO_DYNAMITE_API
const std::string&
info::dynamite::DynamicFunction::name() const noexcept {
    return _name;
}
