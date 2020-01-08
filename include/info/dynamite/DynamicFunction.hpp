//
// Created by tudom on 2019-12-31.
//

#pragma once

#include "_api.hpp"
#include "FunctionTypes.hpp"
#include "DynamicLibrary.hpp"

namespace info::dynamite {
  struct INFO_DYNAMITE_API DynamicFunction {
      // functions
      template<class... Args>
      void operator()(Args&& ...);

      template<class... Args>
      void call(Args&& ...);

      template<class R, class... Args>
      R callReturn[[nodiscard]](Args&& ...);

      // accessors
      AbstractFunction& handle[[nodiscard]]() noexcept;
      const AbstractFunction& handle[[nodiscard]]() const noexcept;

      std::string& name[[nodiscard]]() noexcept;
      const std::string& name[[nodiscard]]() const noexcept;

      // constructor
      DynamicFunction(AbstractFunction, std::string) noexcept;
  private:
      AbstractFunction _handle;
      std::string _name;
  };
}

template<class... Args>
void info::dynamite::DynamicFunction::operator()(Args&& ... args) {
    call(std::forward<Args>(args)...);
}

template<class... Args>
void info::dynamite::DynamicFunction::call(Args&& ... args) {
    callReturn<void>(std::forward<Args>(args)...);
}

template<class R, class... Args>
R info::dynamite::DynamicFunction::callReturn[[nodiscard]](Args&& ... args) {
    return reinterpret_cast<FixedReturnAbstractFunction<R>>(_handle)(std::forward<Args>(args)...);
}

