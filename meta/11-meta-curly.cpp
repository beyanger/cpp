
#include <iostream>

template<typename T>
struct PointerOf {
    using Result = T*;
};

template<typename T>
struct Pointer2Of {
    using Result = T**;
};

#define __pointer(...) typename PointerOf<__VA_ARGS__>::Result

template<typename T>
struct Pointer3Of {
    using Result = typename Pointer2Of<typename PointerOf<T>::Result>::Result;
    using R3 = typename PointerOf<typename PointerOf<typename PointerOf<T>::Result>::Result>::Result;
    // 由于 PointerOf<...>::Result 中存在非具体类型，需要推导类型，所有需要在前面添加 typename
    using RR3 = __pointer(__pointer(__pointer(T)));
};

template<int N, typename T, template<typename> class Func>
struct Times {
    using Result = typename Func<typename Times<N-1, T, Func>::Result>::Result;
};

template<typename T, template<typename> class Func>
struct Times<1, T, Func> {
    using Result = typename Func<T>::Result;
};

template<int N>
struct CharPointer {
    using Result = typename Times<N, char, PointerOf>::Result;
};

template<int N>
struct CharPointer2 : public Times<N, char, PointerOf> {

};

// 元函数转发
template<int N> using CharPointer3 = Times<N, char, PointerOf>;


int main() {
    char c = 'a';
    CharPointer3<1>::Result pc = &c;
    CharPointer3<2>::Result ppc = &pc;
    CharPointer3<3>::Result pppc = &ppc;


    return 0;
}
