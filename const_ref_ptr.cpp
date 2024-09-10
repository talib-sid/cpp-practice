#include <iostream>

int main()
{
    // int x = 5;
    
    // const int &refX = x;
    
    // x*2 which is an rvalue creates a temp memory space 
    // for the computation, and now this memory is referenced
    // via the const ref(reFX) this would not be possible
    // with a normal ref, Eg: int &ref = x*2 would be an err
    
    // const int &refX = x*2;
    
    // Throws an error
    // int &refX = 10;
    // Works
    // const int &refX = 10;
    
     // // // // // // // // // // ///
    // But HOW is this possible ?? //
   // // // // // // // // // // ///
    
    // refX is bound to a temporary object. 
    // Temp Object is an unnamed object created by the compiler when
    // It needs a place to store a result from evaluating an expression.
    
    // Both have diff address spaces, next to each other in memory
    // std::cout << &x << " " << x << " " << &refX << " " << refX << std::endl;



    // // Now what if we use a const ref on a type which is not a const?
    
    // double dval = 3.14;
    // const int &ri = dval;
    // // compiles just fine
    
    // std::cout << dval << " " << &dval << " " << ri << " " << &ri << std::endl;
    // Interesting, we get a diff address and val for this
    // Why, is this so, when we made a reference to an lvalue this time, an object,
    // not a temp variable or a constant expression
    // This happens because when you are trying to assign to a const reference
    // this is what goes into the compiler internall
    /*
        const int &ri = dval;
            Internally->
            const int dval_temp = dval;
            const int &ri = dval_temp;
        This cast happens because of two reasons mainly.
        Firstly because the double type does not match the reference type of ri
        Secondly, because it needs to maintain constant-ncy, which would not possible
        with a non-const type
    */
    

    // Now we try to do something else, how about we try to store an
    // integer within a constant ref of double type
    
    // this works and returns same address for both
    // double dval = 3.14;
    // const double &ri = dval;
    
    
    // however, this throws a type-error
    // error: cannot bind non-const lvalue ref of type ‘double&’ to a value of type ‘int’
    // double dval = 3.14;
    // double &ri = (int)dval;
    
    // however, here both the val and address of the ref changes
    // double dval = 3.14;
    // const double &ri = (int)dval;
    
    // int dval = 5;
    // int &rj = dval;
    // const int &ri = dval;
    
    // even tho ri is bound to the original address of dval, you cannot modify
    // dval using ri
    // ri--;
    // this throws an error, error: decrement of read-only reference ‘ri’
    
    // This works, because its not a const reference, but a normal one
    // rj--;
    
    // std::cout << dval << " " << &dval << " " << ri << " " << &ri << std::endl;
    
    // This is very similar to the functioning to that of const pointers
    // as pointers are objects not references, once they are initialsied
    // they will point to that object for life-time
    
    // int num = 0;
    // int *const numPointer = &num; // numPointer will always point to errNumb
    
    // const double pi = 3.14159;
    // const double *const pip = &pi; // pip is a const pointer to a const obj
    
    // The pointer to a constant type cannot be used to modify the value 
    // of the variable it is pointing to.
    // *pip = 2.72; // error: pip is a pointer to const
    
    // but here
    // if the object to which numPointer points (i.e., num) is nonzero
    // if (*num) {
    //     // errorHandler();
    //     *numPointer = 0; // ok: reset the value of the object to which curErr is bound
    // }
    // here we can do this because, 
    // the POINTER is constant to the variable it is pointing to, not the variable itself
    
    
    // int x = 5;
    // // Both of these work, but do they point to the same memory?
    // int *xPtr = &x;
    // const int *xConstPtr = &x;
    
    // They all do, point to the same memory
    // std::cout << &x << " " << xPtr << " " << xConstPtr;
    
    // But can they both modify our x
    // (*xPtr)--;
    // (*xConstPtr)--; 
    // this throws an error: decrement of read-only location ‘* xConstPtr’
    
    // std::cout << x << " " << &x << " " << xPtr << " " << xConstPtr;
    
    // But, xConstPtr is a const int pointer but not a const pointer itself
    // meaning you can do this
    // xConstPtr--;
    // or even this
    // int y = 5;
    // xConstPtr = &y;
    // Meaning it can point to any new object but read-only access to that memory
    // std::cout << x << " " << &x << " " << xPtr << " " << xConstPtr;
    
    
    // Now this a const x pointer, meaning it will constantly,
    // only and only point to x, it can modify it too
    // int *const constXptr = &x;
    // x = 5;
    // *(constXptr) = 2;
    // It changes value of x successfully
    // std::cout << x << " " << &x << " " << xPtr << " " << constXptr;
    
    char x = 't';
    
    const char *p = &x;
    // char const *p = &x; Equivalent to the above for some motherfucking reason
    
    // this is will obv not work but, there's magic in c++
    // (*p)='c';


    // const_cast is used to remove the const-ness from references and pointers that 
    // ultimately refer to something that is not const

    *const_cast<char*> (p) = 'c';

    std::cout << x << " " << *p << std::endl;
    return 0;

}






