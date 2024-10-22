#include <iostream>

class A{
    // some member varables
    int x1;
    double d1;
    public:
        A(){};
        ~A(){};
};

void foo(A&){
    std::cout << "f1\n"; 
}
void foo(const A&){
    std::cout << "f2\n"; 
}
void foo(A&&){
    // will never return true, because the rval ref is passed here
    std::is_const<A>::value;
    std::cout << "f3\n"; 
}


// we try to perfectly forward
template<typename T>
void callFoo(T&& param){
    // may or may not return true
    // because  anything is acceptable in this param
    std::is_const<T>::value;
    foo(std::forward<T>(param));
    
}


int main(){
    A a1;
    const A a2;
    A a3;

    foo(a1); // calls f1
    foo(a2); // calls f2
    foo(std::move(a1)); // calls f3
    std::cout << '\n';
    // now, to have caller functions, we'd need different helpers,
    // too hectic, instead, we use perf forwarding
    // 3 requirements to have a universal/forwarding ref 

    // 1, Template Type, should be used as Param 
    // 2, This should be an rval ref (T&&)
    // 3, Uses std::forward<T>(value)
    callFoo(a1);
    callFoo(a2);
    callFoo(A{});

}