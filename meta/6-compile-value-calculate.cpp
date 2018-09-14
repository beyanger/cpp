
#include <stdint.h>
#include <iostream>

// value calculate
template<long long X, long long Y>
struct Plus {
    static const long long Value = X + Y;
//    enum { Value = X + Y};
//    上述两种方法保存返回值，作用一样
//    有些编译器对 static const 来保存结果会存在问题, 优先使用 enum
};

template<int Value>
struct Print {
    operator char() {
        return Value + 0xFF;
    }
};


#define UNIQUE_NAME(prefix) prefix##__LINE__
#define __print(...) char UNIQUE_NAME(print_v_) = Print<Plus<__VA_ARGS__>::Value>()
int main() {
    std::cout << Plus<3, 4>::Value << std::endl;

    // 会执行 Print<7>::char() { return 7 + 0xFF; } 编译时产生益处警告
    char print_v = Print<Plus<3, 4>::Value>();
    __print(2, 3);
    return 0;
}
