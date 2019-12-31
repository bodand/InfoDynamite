//
// Created by tudom on 2019-12-28.
//

#ifdef _WIN32
#  ifdef INFO_BUILD_DLL
#    define LIBNM_API __declspec(dllexport)
#    define LIBNM_LOCAL
#  else
#    define LIBNM_API __declspec(dllimport)
#    define INFO_LOCAL
#  endif
#else
#  define LIBNM_API __attribute__((visibility("default")))
#  define LIBNM_LOCAL __attribute__((visibility("hidden")))
#endif

int LIBNM_API square(int i) {
    return i * i;
}

void LIBNM_API param_sqr(int* ret, int i) {
    *ret = i * i;
}

void LIBNM_LOCAL fix_all_the_worlds_problems(void*) {}
