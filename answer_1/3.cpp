#include <iostream>
#include <string>
using namespace std;

class Base {
    public:
        virtual string getClassName() const { string out("Base"); return out; }
};

class Derived: public Base {
    public:
        string getClassName() const { string out("Derived"); return out; } 
};