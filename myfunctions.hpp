#pragma once
#include <iostream>
#include <cstdio>
#include <memory> // for std::unique_ptr
#include <cxxabi.h>
#include <typeinfo>

template<typename T>
void coutAddr(const T& a){
    // Guarantees to deliver addr
    std::cout <<  &a << std::endl;
}

template<typename T>
void coutVal(const T& a){
    // Print the val (may print addr if type is a ref)
    std::cout << a << std::endl;
}

template<typename T>
void coutPtr(const T& a){
    // Print the pointers address
    std::cout << a << std::endl;
}

// abi::__cxa_demangle is used to demangle the type name returned by typeid(a).name().
// The std::unique_ptr with a custom deleter (std::free) 
// ensures proper memory management, as abi::__cxa_demangle allocates 
// memory that needs to be freed.
// status is used to check whether demangling succeeded.
// If it succeeded (status == 0), the demangled name is printed; 
// otherwise, the original mangled name is printed.

template<typename T>
void coutType(const T& a) {
    int status = 0;
    std::unique_ptr<char, void(*)(void*)> realname(
        abi::__cxa_demangle(typeid(a).name(), nullptr, nullptr, &status), std::free);
    
    std::cout << "Type: " << (status == 0 ? realname.get() : typeid(a).name()) << std::endl;
}
