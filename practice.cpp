#include <iostream>
#include <vector>
#include <iterator>
#include "myfunctions.hpp"

std::vector<int> fun1(){
    return {1,2,3};
}

void prtVctr(std::vector<int>::iterator curr, const std::vector<int>::iterator &end){
        if(curr == end) return;        

        std::cout << *curr << ' ';
        prtVctr(++curr,end);
        // prtVctr(curr++,end); goes into inf loop, as the iterator gets inc afterwards

}

void printList(std::vector<int>::const_iterator it, std::vector<int>::const_iterator end) {
    if (it == end) {
        std::cout << std::endl;
        return;
    }
    std::cout << *it << ' ';
    printList(++it, end);
}

int main(){
    std::vector<int> v1 = fun1();

    auto it = v1.begin();
    coutType(it);
    prtVctr(v1.begin(),v1.end());

    int ff(int a, int b = 0, int c = 0);
    char *init(int ht = 24, int wd, char bckgrnd);    

    // for(const auto &a : v1) std::cout << a << '\n';
    return 0;
}