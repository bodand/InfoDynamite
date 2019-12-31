#pragma once

#ifdef _WIN32
#  ifdef LIBNM_DLL
#    ifdef LIBNM_BUILD_DLL
#      define LIBNM_API __declspec(dllexport)
#      define LIBNM_LOCAL
#    else
#      define LIBNM_API __declspec(dllimport)
#      define LIBNM_LOCAL
#    endif
#  else
#    define LIBNM_API
#    define LIBNM_LOCAL
#  endif
#else
#  ifdef LIBNM_DLL
#    ifdef LIBNM_BUILD_DLL
#      define LIBNM_API __attribute__((visibility("default")))
#      define LIBNM_LOCAL __attribute__((visibility("hidden")))
#    else
#      define LIBNM_API
#      define LIBNM_LOCAL
#    endif
#  else
#    define LIBNM_API
#    define LIBNM_LOCAL
#  endif
#endif
