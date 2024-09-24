// Basic Intro to template metaprogramming
// https://github.com/wuye9036/CppTemplateTutorial/blob/master/ReadMe.md

#include <iostream>

// Let's define a template class
template <typename T>
class MyClass {
public:
    T member;
};
// OR
template <typename T> class ClassTemplate {
public:
    T member;
};

template <typename T>
void mymax(T a, T b) {
    std::cout << "max: " << (a > b ? a : b) << std::endl;
}

template <typename T>
T myMax(T a, T b) {
    return a > b ? a : b;
}

template <typename T1, typename T2>
auto Retmax(T1 a, T2 b) {
    return a > b ? a : b;
}

int main() {
    // Compiles fine
    mymax(1, 2);
    mymax(1.1, 2.2);

    // But this will not
    // mymax(1, 2.2); // error: no match for 'operator>' (operand types are 'int' and 'double')
    // mymax(1.1, 2); // error: no match for 'operator>' (operand types are 'double' and 'int')

    // To deal with this, we can implicity tell the compiler to deduce the type as double
    mymax<double>(1, 2.2);
    mymax<double>(1.1, 2);

    auto a = myMax(1, 2);
    auto b = myMax(1.1, 2.2);
    auto c = myMax('a', 'b');
    // This will not compile, because the compiler cannot deduce the type
    // auto d = myMax(1, 2.2); // error: no match for 'operator>' (operand types are 'int' and 'double')
    // Two things we can do now,
    // 1. Explicitly tell the compiler to deduce the type
    auto d = myMax<double>(1, 2.2);
    // or use auto deduction in the function return type, Since c++14, we can do this and
    // let the compiler deduce the type for us

    // Now let's say we hvae a max, whicch does inturn take two arguments, both of which 
    // we can then use something like this
    auto e = Retmax(1, 2.2);
    // now here we force the compiler to deduce the type of the return value
    // and we can do this for any number of arguments






    return 0;
}
