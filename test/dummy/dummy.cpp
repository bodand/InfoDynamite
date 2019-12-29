//
// Created by tudom on 2019-12-28.
//

#ifdef _WIN32
#  ifdef INFO_BUILD_DLL
#    define INFO_API __declspec(dllexport)
#    define INFO_LOCAL
#  else
#    define INFO_API __declspec(dllimport)
#    define INFO_LOCAL
#  endif
#else
#  define INFO_API __attribute__((visibility("default")))
#  define INFO_LOCAL __attribute__((visibility("hidden")))
#endif

int INFO_API square(int i) {
    return i * i;
}

void INFO_API param_sqr(int* ret, int i) {
    *ret = i * i;
}

void INFO_LOCAL fix_all_the_worlds_problems(void*) {}
