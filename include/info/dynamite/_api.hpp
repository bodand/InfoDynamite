#pragma once

#ifdef _WIN32
#  ifdef INFO_DYNAMITE_DLL
#    ifdef INFO_DYNAMITE_BUILD_DLL
#      define INFO_DYNAMITE_API __declspec(dllexport)
#      define INFO_DYNAMITE_LOCAL
#    else
#      define INFO_DYNAMITE_API __declspec(dllimport)
#      define INFO_DYNAMITE_LOCAL
#    endif
#  else
#    define INFO_DYNAMITE_API
#    define INFO_DYNAMITE_LOCAL
#  endif
#else
#  ifdef INFO_DYNAMITE_DLL
#    ifdef INFO_DYNAMITE_BUILD_DLL
#      define INFO_DYNAMITE_API __attribute__((visibility("default")))
#      define INFO_DYNAMITE_LOCAL __attribute__((visibility("hidden")))
#    else
#      define INFO_DYNAMITE_API
#      define INFO_DYNAMITE_LOCAL
#    endif
#  else
#    define INFO_DYNAMITE_API
#    define INFO_DYNAMITE_LOCAL
#  endif
#endif
