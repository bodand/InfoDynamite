//
// Created by tudom on 2019-12-31.
//

#pragma once

#include <exception>
#include <string>

#include "../_api.hpp"

namespace info::dynamite {
  struct INFO_DYNAMITE_API no_such_function : std::exception {
      const char* what[[nodiscard]]() const noexcept override;

      no_such_function(std::string) noexcept;
  private:
      std::string _function;
  };
}
