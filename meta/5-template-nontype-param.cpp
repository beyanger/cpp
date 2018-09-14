
#include <iostream>
#include <string>

// 模板的非类型参数, 可以是整型常量(包含enum, int uint, long, long long)，具有外部链接的指针(函数指针，类成员函数指针)
// 也支持具有外部链接的字符串常量指针
// 不支持浮点数
template<const char *iname>
struct Token {
    std::string name{iname};
};

extern const char sname[] = "hello";

// 模板支持的参数类型
// 1，类型参数， 用 typename 或者 class
// 2, 非类型参数，参考上述
// 3，模板参数, 用 template<...> class XXX, 用模板作为模板的参数


int main() {
    //Token<"hello"> t1; error
    const char *str = "hello";
    //Token<str> t2; error
    // 具有外部链接的字符串常量指针
    Token<sname> t;
    
    std::cout << t.name << std::endl;
    return 0;
}
