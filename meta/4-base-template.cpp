
#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept>

template<typename T, typename Allocator = std::allocator<T>>
struct Array {
    Array() {
        ele.resize(100);
    }
    void put(size_t index, const T& t) {
        ele[index] = t; 
    }
    T get(size_t index) {
        return ele[index];
    }

    std::vector<T, Allocator> ele;
};

template<typename T, 
    template<typename E, typename Allocator = std::allocator<E>> typename Container = std::vector>
struct Stack {
    Stack() {
        std::cout << "orgin " << std::endl;
    }
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



// Stack 的第二个参数已经被具体化为 Array ，称为特化版本, 部分特化，偏特化
template<typename T>
struct Stack<T, Array> {
    
    Stack() : size(0) { 
        std::cout << "part special" << std::endl;
    } 

    void push(const T& e) {
        elems.put(size++, e);
    }

    T pop() {
        if (empty()) throw std::out_of_range("Stack<>::pop empty!");
        return elems.get(--size);
    }
    bool empty() const {
        return size == 0;
    }

private:
    size_t size;
    Array<T> elems;
};

// Stack的两个参数全被具体化，称为全特化
template<>
struct Stack<int, Array> {
    
    Stack() : size(0) { 
        std::cout << "full special" << std::endl;
    } 

    void push(const int & e) {
        elems.put(size++, e);
    }

    int pop() {
        if (empty()) throw std::out_of_range("Stack<>::pop empty!");
        return elems.get(--size);
    }
    bool empty() const {
        return size == 0;
    }

private:
    size_t size;
    Array<int> elems;
};

/*
 *  模板的定义可以嵌套
 *  但模板的特化不可以嵌套
 * */



using std::cout;
using std::endl;

int main() {
    Stack<int, Array> sa;
    Stack<int, Array> sc;
    Stack<double, Array> sb;
    Stack<int, std::vector> sk;

    for (int i = 0; i < 10; i++) 
        sk.push(i);
    while (!sk.empty()) 
        cout << sk.pop();
    cout << endl;
    return 0;
}

