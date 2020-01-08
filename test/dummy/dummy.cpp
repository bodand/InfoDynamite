//
// Created by tudom on 2019-12-28.
//

#ifdef _WIN32
#  define DUMMY_API __declspec(dllexport)
#  define DUMMY_LOCAL
#else
#  define DUMMY_API __attribute__((visibility("default")))
#  define DUMMY_LOCAL __attribute__((visibility("hidden")))
#endif

int DUMMY_API square(int i) {
    return i * i;
}

void DUMMY_API param_sqr(int* ret, int i) {
    *ret = square(i);
}

void DUMMY_LOCAL fix_all_the_worlds_problems(void*) {}
