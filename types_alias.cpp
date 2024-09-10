#include <iostream>
#include "myfunctions.hpp"

// you can declare talib as int
typedef int talib;
// you can now also make a ptr with it
typedef talib *talibPtr;
// new keyword, using
using tal = talib;
using talu = tal;

int main(){
    talib i  = 5;
    talibPtr j = &i;
    tal k = 10;

    // prints same address
    coutAddr(i);
    coutPtr(j);

    // Works as an integer
    coutVal(k);

    // We define pstring as a pointer to a char
    typedef char *pstring;
    
    const pstring cstr = 0; // cstr is a constant pointer to char
    // pstring const cstr = 0; // Equivalent for some motherfucking reason

    const pstring *ps; // ps is a pointer to a constant pointer to char
    // pstring const *ps; // Equivalent for some motherfucking reason
    

    // std::cout << j << std::endl;    
    
    // auto ordinarily ignores top-level consts
    // As usual in initializations, low-level consts, such as when an initializer is a pointer to const, are kept

    // const int ci = i, &cr = ci;
    // auto b = ci; // b is an int (top-level const in ci is dropped)
    // auto c = cr; // c is an int (cr is an alias for ci whose const is top-level)
    // auto d = &i; // d is an int* (& of an int object is int*)

    // auto e = &ci; // e is const int* (& of a const object is low-level const)

    // If we want the deduced type to have a top-level const, we must say so explicitly:
    // const auto f = ci; // deduced type of ci is int; f has type const int

    // We can also specify that we want a reference to the auto-deduced type. Normal
    // initialization rules still apply:
    // auto &g = ci; // g is a const int& that is bound to ci
    // auto &h = 42; // error: we can’t bind a plain reference to a literal
    // const auto &j = 42; // ok: we can bind a const reference to a literal
    //NOTE:
    //  When we ask for a reference to an auto-deduced type, top-level consts in the
    // initializer are not ignored. As usual, consts are not top-level when we bind a
    // reference to an initializer

    // As usual, the initializers must provide consistent
    // auto-deduced types:
    // auto k = ci, &l = i; // k is int; l is int&
    // auto &m = ci, *p = &ci; // m is a const int&; p is a pointer to const int
    // // error: type deduced from i is int; type deduced from &ci is const int
    // auto &n = i, *p2 = &ci;

    // For such cases, the new standard introduced a second type specifier, decltype,
    // which returns the type of its operand. The compiler analyzes the expression to
    // determine its type but does not evaluate the expression:

    // decltype(f()) sum = x; // sum has whatever type f returns

    // Here, the compiler does not call f, but it uses the type that such a call would return
    // as the type for sum. That is, the compiler gives sum the same type as the type that
    // would be returned if we were to call f.

    return 0; 
    
}