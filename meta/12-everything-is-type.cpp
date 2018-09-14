
#include <iostream>
template<typename T, typename U>
struct IsTypeEqual {
    enum {Result = false};
};

template<typename T>
struct IsTypeEqual<T, T> {
    enum {Result = true};
};

template<int N, int M>
struct IsNumEqual {
    enum {Result = false};
};

template<int N>
struct IsNumEqual<N, N> {
    enum { Result = true};
};

template<int V>
struct IntType {
    enum {Value = V };
    using Result = IntType<V>;
};


template<bool V> struct BoolType;
template<>
struct BoolType<true> {
    enum { Value = true };
    using Result = BoolType<true>;
};

template<>
struct BoolType<false> {
    enum {Value = false};
    using Result = BoolType<false>;
};

using TrueType = BoolType<true>;
using FalseType = BoolType<false>;

template<typename T, typename U>
struct IsEqual {
    using Result = FalseType;
};
template<typename T>
struct IsEqual<T, T> {
    using Result = TrueType;
};

#define __int(v) typename IntType<v>::Result
#define __bool(...) typename BoolType<__VA_ARGS__>::Result
#define __true() typename TrueType::Result
#define __false() typename FalseType::Result

#define __is_ea(...) typename IsEqual<__VA_ARGS__>::Result

template<typename T>
struct Value {
    enum {Result = T::Value};
};

#define __value(...) Value<__VA_ARGS__>::Result

template<typename T1, typename T2> struct Add;

template<int V1, int V2>
struct Add<IntType<V1>, IntType<V2>> {
    using Result = IntType<V1 + V2>;
};

#define __add(...) typename Add<__VA_ARGS__>::Result


using namespace std;

int main() {
    cout << IsEqual<TrueType, BoolType<true>>::Result::Value << endl;
    cout << IsEqual<FalseType, BoolType<true>>::Result::Value << endl;
    cout << __value(TrueType) << endl;

    cout << __value(__add(__int(3), __int(5))) << endl;
    cout << __value(__bool(true)) << endl;

    return 0;
}
