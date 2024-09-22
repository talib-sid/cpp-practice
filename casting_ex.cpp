#include <iostream>
#include <string>
#include "myfunctions.hpp"

struct student{
    int age = 10;
    std::string name = "_";
} talib;


int main(){
    // first a bit on the void *
    // points to any raw memory in the adr space
    // cannot be deferenced without the usage of casting 

    // int x = 5;
    
    // void *vPtr = &x; // valid
    // // invalid operations
    // *vPtr = 10;
    // std::cout << *vPtr << std::endl;
    
    // // now to valid them we can do this
    // int *nPtr = static_cast<int*> (vPtr);
    // std::cout << *nPtr << std::endl;

    // static cast is just basic cast, similar to (int) x
    // in that of C-style casting
    
    const int a = 10;

    // now let's try to do the same with a const ptr
    const int* cPtr = &a;
    // // obviously this does not fucking work either
    // int *newcPtr = cPt   r;
    // // a value of type "const int *" cannot be used to 
    // // initialize an entity of type "int *"C/C++(144)

    // // this also will not work
    // int *newcPtr = static_cast<int*> (cPtr);
    // // static_cast cannot cast away const or other type qualifiersC
    
    // let's use a const_cast now, this will be able to const cast, yay!!
    int *newcPtr = const_cast<int*> (cPtr);
    // all these return same addr, meaning
    // we have removed the const-ness away from the cPtr
    coutAddr(a);
    coutPtr(newcPtr);
    coutPtr(cPtr);
    
    // we can also use this new ptr to make modifs
    (*newcPtr)+=2;
    // // note: you cannot use the const element itself, a in this case
    // // to make the change, as that element is still read-only type
    // a+=2;
    coutVal(a);

    
    coutType(a),coutType(newcPtr),coutType(cPtr);
    // // also, this does not remove the const-ness from the original const ptr
    // (*cPtr)++; // error
    // coutVal(a);
    

    // another bogus term
    // reinterpret_cast
    // copied from primer 
    // reinterpret_cast generally performs a low-level reinterpretation of the bit
    // pattern of its operands. As an example, given the following cast
    int t = 10;
    int *ip = &t;
    char *pc = reinterpret_cast<char*>(ip);
    
    // we must never forget that the actual object addressed by pc is an int, 
    // not a character. Any use of pc that assumes it’s an 
    // ordinary character pointer is likely to fail at run time. For example:
    std::string str(pc);
    // std::cout << str;
    // is likely to result in bizarre run-time behavior.
    // The use of pc to initialize str is a good example of why reinterpret_cast
    // is dangerous. The problem is that types are changed, yet there are no warnings or
    // errors from the compiler. When we initialized pc with the address of an int, there
    // is no error or warning from the compiler because we explicitly said the conversion
    // was okay. Any subsequent use of pc will assume that the value it holds is a char*.
    // The compiler has no way of knowing that it actually holds a pointer to an int.
    // Thus, the initialization of str with pc is absolutely correct—albeit in this case
    // meaningless or worse! Tracking down the cause of this sort of problem can prove
    // extremely difficult, especially if the cast of ip to pc occurs in a file separate from
    // the one in which pc is used to initialize a string.
    // A reinterpret_cast is inherently machine dependent. 
    
    // Safely using reinterpret_cast requires completely understanding the 
    // types involved as well as the details of how the compiler implements the cast.
    
   
    return 0;
}