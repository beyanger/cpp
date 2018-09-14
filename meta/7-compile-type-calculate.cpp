
#include <iostream>

template<typename T>
struct PointerOf {
    //typedef T* Type;
    using Type = T*;
//  上述两种写法效果相同, 优先使用 using (C++11标准)
};

int main() {
    PointerOf<const char>::Type s = "hello world!";
    std::cout << s << std::endl;
    return 0;
}

