#include <iostream>

class ABC{
    // Member variable
    int x = 0;
    int y = 1;
    int z = 3;
    public:
        void func1() const{
            // If you use const keyword post the function declaration
            // then you cannot modify any member variables within this fun

            // x = x + 10; // Error (at Compile time)
            // vscode error: expression must be a modifiable lvalueC/C++(137)
            // compile error: assignment of member 'ABC::x' in read-only object

            int a = x;
            a = a + 10; // you can make a copy for the same
            return;
        }

        void func2(const int rhs){
            // now this variable that has been passed has to stay constant
            // within this funciton
            // rhs++ // will throw an error
            // expression must be a modifiable lvalue
            std::cout << rhs-2 << std::endl;
        }
        void func3(const int& rhs){
            // here you can access the address of this rhs
            // but cannot modify the original variable itself
            // so, we try to assign it's address to another lvalue instead
            // and then try to modify it later on.
            // int &lhs = rhs;
            // qualifiers dropped in binding reference of type "int &" to initializer of type "const int"
            // error: binding 'const int' to reference of type 'int&' discards qualifiers
        }
};
int main(){
    int a = 5;
    ABC obj;
    obj.func1();
    obj.func2(a);
    obj.func3(a);

    std::cout << a << std::endl;
}