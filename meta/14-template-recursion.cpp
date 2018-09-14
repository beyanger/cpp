
template<int V>
struct IntType {
    enum {Value = V };
    using Result = IntType<V>;
};

template<typename T1, typename T2> struct Add;

template<int V1, int V2>
struct Add<IntType<V1>, IntType<V2>> {
    using Result = IntType<V1 + V2>;
};

template<typename ...Numbers> struct Sum;

template<typename Number, typename ...LeftNumbers>
struct Sum<Number, LeftNumbers...> {
    using Result = typename Add<Number, typename Sum<LeftNumbers...>::Result>::Result;
};

template<> 
struct Sum<> {
    using Result = IntType<0>;
};

template<int ...Num> 
struct Suma;
template<int N, int ...Left>
struct Suma<N, Left...> {
    static const int Value = N + Suma<Left...>::Value;
};
template<int N> 
struct Suma<N> {
    static const int Value = N;
};

#include <iostream>
using namespace std;

int main() {
    cout << Suma<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>::Value << endl;
    return 0;
}

