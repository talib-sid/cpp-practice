#include <iostream>
// https://en.cppreference.com/w/cpp/language/copy_elision

// Copy elision is an optimization implemented by most compilers to prevent extra (potentially expensive) 
// copies in certain situations. It makes returning by value or pass-by-value feasible in practice (restrictions apply).

// Also called as Named return value optimization (NRVO)

// Prvalue semantics ("guaranteed copy elision")
// Since C++17, a prvalue is not materialized until needed, and then it is constructed directly 
// into the storage of its final destination. This sometimes means that even when the language 
// syntax visually suggests a copy/move (e.g. copy initialization), no copy/move is performed 
// which means the type need not have an accessible copy/move constructor at all. Examples include:


class S{
    public:
        S(){std::cout<<"default con\n";}
        S(const S& s){std::cout<<"copy con\n";}
        void someOp(){
            std::cout << "some operation called\n";
        }
        // S operator=(){std::cout<<"assigment called\n"};
        ~S(){std::cout<<"destr called\n";}
};

S f1(){
    // returns the struct directly;
    return S();
}

S f2(){
    S s = S();
    s.someOp();
    return s;
}

int main(){
    // here, the copy constructor is not called, because copy-elision happens
    S temp1 = f1();
    // here, it may or may not happen;
    S temp2 = f2();

    // Limitations are here
    // https://medium.com/@toramanbatur/exploring-the-limitations-of-named-return-value-optimization-nrvo-in-c-compilers-examples-and-b88b78fd1ae8

    return 0;
}