#pragma once
#include <iostream>
#include <cstdio>
#include <typeinfo>

template<typename T>
void coutAddr(const T& a){
    std::cout <<  &a << std::endl;
}

template<typename T>
void coutVal(const T& a){
    std::cout << a << std::endl;
}

template<typename T>
void coutPtr(const T& a){
    std::cout << a << std::endl;
}


template<typename T>
void coutType(const T& a) {
    std::cout << "Type: " << typeid(a).name() << std::endl;
}





// int x = 5;
// int y = 10;
// uint32_t sum = (x+y);

