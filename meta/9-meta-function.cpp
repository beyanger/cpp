
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

int main() {
    int v = 0;
    PointerOf<int>::Result pv = &v;
    Pointer2Of<int>::Result ppv = &pv;
    Pointer3Of<int>::Result pppv = &ppv;
    
    return 0;
}
