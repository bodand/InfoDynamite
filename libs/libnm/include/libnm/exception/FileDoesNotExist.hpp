//
// Created by tudom on 2019-12-22.
//

#pragma once

#include <exception>
#include <string>
#include <string_view>

#include "libnm/_api.hpp"

namespace libnm {
  struct LIBNM_API file_does_not_exist : std::exception {
      [[nodiscard]]
      const char* what() const noexcept override;

      explicit file_does_not_exist(std::string_view filename);
  private:
      std::string _filename;
  };
}
