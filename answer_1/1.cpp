#include <iostream>
#include <string>
using namespace std;

class Base {
    public:
        virtual string getClassName() {
            return "Base";
        }
};

class Derived: public Base {
    public:
        string getClassName() {
            return "Derived";
        }
};

int main() {
    Base * base = new Base();
    cout << base->getClassName();
    
    cout << " ";
    
    Base * derived = new Derived();
    cout << derived->getClassName();
}