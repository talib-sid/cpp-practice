#include <iostream>

// What is this shit, what does it mean
// Return value optimisation,  (similar Named-RVO done in copy_elision.cpp)
// https://www.youtube.com/watch?v=WyxUilrR6fU

// It is a compiler optimisation that eliminates the creation of temp. objects by directly
// constructing the return value in the memory location of the caller

class MyObj{
    int elem;
    public:
        MyObj(){}
        MyObj(int a): elem(a){
            std::cout << "i am normal ctor\n";
        }
        MyObj(const MyObj& obj) {elem=obj.elem;
            std::cout << "i am copy ctor\n";
        }
};

// NRVO
MyObj foo1(){
    MyObj temp(5);
    return temp;
}
// RVO
MyObj foo2(){
    return MyObj(5);
}

// Cool, when does it fail tho, 
// when we want it to fail delib. using the shit flags
// secondly, like this

class MyObjChild:public MyObj{
    public:
        MyObjChild(){}
};
// Inheritance Fails RVO, whenever return is not what we expected
MyObj foo3(){
    return MyObjChild();
}

int main(){
    MyObj a,b;

    // upon compilation, normal ctor is called for both
    a=foo1();
    b=foo2();
    // i am normal ctor
    // i am normal ctor

    // now when we try to call the same functions with diff flags
    // nrvo disabled by using -O1 and -fno-elide-constructors
    // we get different results
    //  i am normal ctor
    //  i am copy ctor 
    //  i am normal ctor
    
    // why do we get 2 instructions for foo1() but not foo2()
    // this is bc URVO or RVO is guaranteed by all compilers post c++17
    // whereas NRVO, which also works on normal compilation is not a compulsory
    // clause on the compiler and gets disabled by our flags,calling the normal 
    // ctor for the temp obj creation, then the copying into B by foo2()'s return



}