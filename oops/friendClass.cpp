#include <iostream>
#include <string>
#include <string_view>


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