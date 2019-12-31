#pragma once

#ifdef _WIN32
#  ifdef LIBLUCENT_DLL
#    ifdef LIBLUCENT_BUILD
#      define LIBLUCENT_API __declspec(dllexport)
#      define INFO_LOCAL
#    else
#      define LIBLUCENT_API __declspec(dllimport)
#      define LIBLUCENT_LOCAL
#    endif
#  else
#    define LIBLUCENT_API
#    define LIBLUCENT_LOCAL
#  endif
#else
#  ifdef LIBLUCENT_DLL
#    ifdef LIBLUCENT_BUILD
#      define LIBLUCENT_API __attribute__((visibility("default")))
#      define LIBLUCENT_LOCAL __attribute__((visibility("hidden")))
#    else
#      define LIBLUCENT_API
#      define LIBLUCENT_LOCAL
#    endif
#  else
#    define LIBLUCENT_API
#    define LIBLUCENT_LOCAL
#  endif
#endif
