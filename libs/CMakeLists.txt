include(DependencyInclude.cmake)

# Magic Enum - MIT license
# https://github.com/Neargye/magic_enum
# Description: Static reflection for enum-types.
# Used by:
#  - `libnm`: The arch endianness is an enum whose handling is eased
add_subdirectory(magic_enum)

# libnm - BSD 3-Clause license
# Homegrown
# Description:
#  A library to supply the functionality of the POSIX `nm` utility, mostly, or
#  actually just a small subset of it. Displays dynamic function signatures from
#  a shared object or dynamically loadable library, from which one can guess,
#  yes, it is cross-platform on ELF users and Windows.
add_subdirectory(libnm)

# liblucent - BSD 3-Clause license
# Homegrown
# Description:
#  A library to supply a symbol demangling function which works on the common
#  ABI implementations including the Itanium ABI, with libc++ and libstdc++ standard
#  libraries and the Microsoft ABI with the STL standard library.
#  If it cannot figure out a built-in function to call it calls Boost.Core's demangle,
#  to which's functionality the provided Demangle function is equivalent.
add_subdirectory(liblucent)
