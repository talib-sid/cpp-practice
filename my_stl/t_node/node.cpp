#include <iostream>
#include <string>
#include "node.hpp"
// #include "./myfunctions.hpp"
#include <myFuncs.h>

int main(){
    // Node <int> node(1);
    Node <std::string> node2("Hello");

    std::cout << node2.get_data();

    // node2.left = 
    auto x = new Node<std::string>(" World");
    // std::cout << << std::endl;
    coutType(x);
    // std::cout << node2.left->get_data();    

    // node2.print_data();
    
    // node.print_data();
    return 0;

}