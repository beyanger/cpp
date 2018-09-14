
#include <iostream>
template<int N>
struct Factorial {
    //static const int Value = N * Factorial<N-1>::Value;
    enum { Value = N * Factorial<N-1>::Value };
};

template<>
struct Factorial<1> {
    // static const int Value = 1;
    enum { Value = 1 };
};

int main() {
    std::cout << Factorial<10>::Value << std::endl;
    std::cout << Factorial<9>::Value << std::endl;

    return 0;
}
