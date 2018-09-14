
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


template<typename Condition, typename Then, typename Else> 
struct IfThenElse;

template<typename Then, typename Else>
struct IfThenElse<TrueType, Then, Else> {
    using Result = Then;
};

template<typename Then, typename Else> 
struct IfThenElse<FalseType, Then, Else> {
    using Result = Else;
};

template<typename T>
struct Value {
    enum {Result = T::Value};
};

#define __value(...) Value<__VA_ARGS__>::Result

#define __bool(...) typename BoolType<(__VA_ARGS__)>::Result
#define __if(...) typename IfThenElse<__VA_ARGS__>::Result

template<typename T, typename U>
using LargerType = __if(__bool(sizeof(T) > sizeof(U)), T, U);

// some trouble here
template<typename T, typename U>
struct IsConvertible {
private:
    using Yes = char;
    struct No { char dummy[2]; };
    static Yes test(U);
    static No test(...);
    static T self();
public:
    using Result = BoolType<(sizeof(test(self()))==sizeof(Yes))>;
};

#define __is_convertible(a, b) IsConvertible<a, b>::Result::Value


#include <iostream>
using namespace std;
int main() {
    LargerType<int, char> b;

    cout << __is_convertible(char *, void *) << endl;
    cout << __is_convertible(int, long) << endl;
    return 0;
}
