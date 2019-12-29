//
// Created by tudom on 2019-12-22.
//

#pragma once

#include <exception>
#include <string>
#include <string_view>

namespace libnm {
  struct file_not_object : std::exception {
      [[nodiscard]]
      const char* what() const noexcept override;

      explicit file_not_object(std::string_view filename);
  private:
      std::string _filename;
  };
}
