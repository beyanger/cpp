
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
template<typename T, typename U>
struct InnerFunc {
    static const int Value = 20;
};
template<typename T>
struct InnerFunc<T, T> {
    static const int Value = 10;
};
template<typename T>
struct OuterFunc {
    template<typename U, typename V>
    using Result = InnerFunc<U, V>;
};

int main() {
    int v = 0;
    PointerOf<int>::Result pv = &v;
    Pointer2Of<int>::Result ppv = &pv;
    Pointer3Of<int>::Result pppv = &ppv;
    Times<4, int, PointerOf>::Result ppppv = &pppv;
    std::cout << OuterFunc<int>::Result<int, double>::Value << std::endl;
    std::cout << OuterFunc<int>::Result<int, int>::Value << std::endl;
    return 0;
}
