//
// Created by tudom on 2019-12-30.
//

#pragma once
#include <exception>
#include <string>

#include "../_api.hpp"

namespace libnm {
  struct LIBNM_API corrupted_elf_object : std::exception {
      [[nodiscard]]
      const char* what() const noexcept override;
  };

  struct LIBNM_API unexplainable_elf_bit_format : corrupted_elf_object {
      [[nodiscard]]
      const char* what() const noexcept override;

      unexplainable_elf_bit_format(uint8_t byte);
  private:
      std::string _byte;
  };

  struct LIBNM_API no_sections : corrupted_elf_object {
      const char* what() const noexcept override;
  };

  struct LIBNM_API inconsistent_section_header_table : corrupted_elf_object {
      const char* what() const noexcept override;
  };

  struct LIBNM_API inconsistent_section_header_size : corrupted_elf_object {
      const char* what() const noexcept override;
  };
}
