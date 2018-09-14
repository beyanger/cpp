
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <map>
#include <string>

using namespace std;


template<typename Base>
class Reflection {
public:
    template<typename Sub>
    static std::string type_name() {
        return TypeName<Sub>::type_name();
    }
    template<typename Sub>
    static std::string type_name(Sub) {
        return TypeName<Sub>::type_name();
    }
    static Base* create(const std::string& name) {
        return (*s_creator[name])();
    }
private:
    class AllocatorBase {
    public:
        virtual Base* operator()() = 0;
    };
    template<typename T>
    class Allocator : public AllocatorBase {
    public:
        T* operator()() {
            return new T;
        }
    };
    template<typename Sub>
    class Registery {
    public:
        Registery() {
            s_creator[get_name()] = new Allocator<Sub>();
        }
        static std::string get_name() {
            return typeid(Sub).name();
        }
    };
    template<typename Sub>
    class TypeName {
    public:
        static std::string type_name() {
            return s_registery.get_name();
        }
    private:
        static Registery<Sub> s_registery;
    };
    static std::map<std::string, AllocatorBase *> s_creator;
};

template<typename Base>
std::map<std::string, typename Reflection<Base>::AllocatorBase *> Reflection<Base>::s_creator;

template<typename Base>
template<typename Sub>
Reflection<Base>::Registery<Sub> Reflection<Base>::TypeName<Sub>::s_registery;

class MapFn {
public:
    virtual void call() = 0;
};

class UserMapFn : public MapFn {
    void call() {
        puts("User Map Fn called");
    }
};


template<typename x, typename y>
struct Cons<x, y>

int main(int argc, char **argv) {
    if (argc == 1) {
        std::string cmd = "";
        cmd += argv[0];
        cmd += " \"" + Reflection<MapFn>::type_name<UserMapFn>() + "\"";
        std::cout << cmd << std::endl;
        system(cmd.c_str());
        return 0;
    }
    std::cout << "in sub process" << std::endl;
    std::string name = argv[1];

    Reflection<MapFn>::create(name)->call();
}
