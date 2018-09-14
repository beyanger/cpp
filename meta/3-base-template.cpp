
#include <deque>
#include <vector>
#include <stdexcept>


template<typename T, 
    template<typename E, typename Allocator = std::allocator<E>> class Container = std::vector>
struct Stack {
    void push(const T& e) {
        elems.push_back(e); 
    }

    T pop() {
        if (empty()) throw std::out_of_range("Stack<>::pop empty!");
        T e = elems.back();
        elems.pop_back();
        return e;
    }
    bool empty() {
        return elems.empty();
    }
    
private:
    Container<T> elems;
};


int main() {
    Stack<int, std::deque> sk;
    Stack<int, std::vector> sv;
    for (int i = 0; i < 10; i++) 
        sk.push(i);
    while (!sk.empty()) 
        sk.pop();
    return 0;
}
