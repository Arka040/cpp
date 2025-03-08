#include <iostream>
#include <string>

using namespace std;

class A {
    int a;
    A(int i = 0) : a(i) {};
    A (const A & cop) {
        this -> a = cop.a;
    };
    public:
        static A* init(int i = 0) {    // static необходим для обращения к функции класса без создания объекта этого класса
            return new A(i);
        }    

        void print() {
            cout << this -> a << endl;
        }

};


int main () {
    A* a1 = A::init(3495);
    a1 -> print();

    A* a2 = a1;
    a2 -> print();

}
