#include <iostream>
#include <string>

class Str{
    private:
        std::string *str;
    public:
        // Default Constructor
        Str(): str(new std::string("")){
            std::cout << "default con" << std::endl;
        }
        
        // Value Constructor
        Str(const std::string& s): str(new std::string(s)){
            std::cout << "con by value" << std::endl;
        }

        // Copy constructor
        Str(const Str& s): str(new std::string(*(s.str))){
            std::cout << "copy con" << std::endl;
        } 

        // Move constructor
        Str(Str&& s) noexcept : str(std::move(s.str)){
            s.str = nullptr;  // Nullify the rvalue's pointer
            std::cout << "move con" << std::endl;
        }

        ~Str(){
            if(str){
                std::cout << "decon for " << this << "called\n";
            }
        }

        void print() const{
            if(str){
                for(auto &ch : *str) std::cout << ch;
            }
            else{
                std::cout << "string is null";
            }
            std::cout << '\n';
        }
};
class Widget{
    private:
        int *lhs;
        bool even;
    public:
        // Copy constructor using Lvalue reference
        Widget(const int& elem) : even{*lhs%2==0}{
            std::cout << "copy con" << std::endl;
            // lhs = elem;c
            std::cout << &elem << " " << &lhs << std::endl << std::endl;
        
        }
        // Move Constructor using Rvalue reference
        Widget(int&& elem) : lhs{&elem}, even{*lhs%2==0}{
            std::cout << "move con" << std::endl;
            std::cout << &elem << " " << &lhs << std::endl;
            // lhs returns the same address as &dud
        }
        ~Widget(){
            if(lhs){
                std::cout << "destroying this" << std::endl;
            }
        }
};


void testStrings(){
    std::string s = "blabla";
    std::cout << "addr of s " << &s << std::endl;
    Str s1();
    Str s2(s);
    Str s3(s2);
    Str s4(std::move(s3));
    int buffer = 5;
}

int main(){
    // int dud = 10;
    // std::cout << &dud << std::endl;
    // // copying dud's value into AA
    // Widget AAA(dud);

    // // moving dud's value, stealing the address space
    // Widget AAB(std::move(dud)); 

    // // this reamins intact unless u steal ownership in the move const.
    // // std::cout << "dud's address :" << &dud << std::endl;

    // int buffer = 1;
    // testStrings();
    return 0;
}
