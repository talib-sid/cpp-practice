#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <complex>

// compile by: 
// g++ -std=c++17 Wall ctad.cpp -o ctad && ./ctad
// compile time argument deduction
// C++17 onwards, we have CTAD, which is a template argument deduction for class types
// This allows us to use the constructor to deduce the type of the class
// This is useful when we have a template class, and we want to use the constructor to deduce the type
// of the class


// custom CTAD class and demonstration
template <typename T>
class ourVector {
    T* data;
    size_t size;
    size_t capacity;
public:
    // Constructors
    ourVector(): size(0), capacity(0), data(nullptr) {}
    ourVector(int n);
    ourVector(int n, T val);
    ourVector(const ourVector& other);
    ourVector(ourVector&& other);
    ourVector& operator=(const ourVector& other);
    ourVector& operator=(ourVector&& other);
    ourVector(std::initializer_list<T> lst) {
        std::cout << "ourVector(std::initializer_list<T> lst)" << std::endl;
    }
    ~ourVector();

};

int main() {

    // Before C++17, we had to explicitly specify the type of the class
    std::pair<int, int> p1(1, 2);
    // Now we can use CTAD to deduce the type of the class
    std::pair p2(1, 2);
    // We can also use CTAD to deduce the type of the class
    std::pair p3(1, 2.2);
    // We can also use CTAD to deduce the type of the class
    std::pair p4('a', 'b');

    // all of the above are the same, and the compiler will deduce the type of the class
    // and we can also do this for user defined types
    std::vector v1{1, 2, 3, 4, 5};

    // Earlier, we had to explicitly specify the type of the class
    std::complex<double> c1(1.0, 2.0);
    // Now
    std::complex c2 = {1.0, 2.0};



// CTAD for user defined types
// ourVector<int> customVec{1, 2, 3, 4, 5};
// we cant use this currently, bc we havent defined the constructors but
// what happens here is that we are using the initializer list constructor
// to initialize the vector
    



    return 0;
}
