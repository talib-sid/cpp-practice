#include <iostream>
#include <string>
#include <string_view>

// The friend function provides us with a way to access private 
// data but it also has its demerits


// A friend function is able to access members without the need of inheriting the class.
// acts as a bridge between two classes by accessing their private data.
// It can be used to increase the versatility of overloaded operators.
// Friend functions cannot do any run-time polymorphism in their members.
// Friendship is not inherited

class Account{
    private:
        std::string name;
        unsigned long balance;

    public:
        Account (){}
        Account (std::string_view s, unsigned long b) : name(s),balance(b){}
        ~Account(){}

        // without this line, getBal not compile
        // as name and balance are encapsulated
        friend void getBal(Account&);
        friend void increaseBal(Account& acc, unsigned long amount);

    // without this, increaseBal and decreaseBal does not compile
    friend class Admin;
};

void getBal(Account& acc){
    std::cout << acc.name << " has " << acc.balance << '\n';
}

class Admin{
    public:
        void increaseBal(Account& acc, unsigned long amount){
            acc.balance += amount;
        }
        void decreaseBal(Account& acc, unsigned long amount){
            acc.balance -= amount;
        }
};

int main(){
    Account talibAcc("Talib",500);
    getBal(talibAcc);

    Admin admin;

    admin.increaseBal(talibAcc,10000);
    getBal(talibAcc);
    admin.decreaseBal(talibAcc,5500);
    getBal(talibAcc);



}