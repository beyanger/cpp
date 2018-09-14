
#include <deque>
#include <vector>
#include <stdexcept>


template<typename T, typename Container = std::vector<T>>
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
    Container elems;
};


int main() {
    Stack<int, std::deque<int>> sk;
    for (int i = 0; i < 10; i++) 
        sk.push(i);
    while (!sk.empty()) 
        sk.pop();
    return 0;
}
