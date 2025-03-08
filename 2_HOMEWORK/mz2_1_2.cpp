#include <iostream>
#include <string>

using namespace std;

class A {
    int a;
    static A* baseinit;      
    A(int i = 0) : a(i) {};
    A (const A & cop) {
        this -> a = cop.a;
    };
    public:
        static A* init(int i = 0) {    // static необходим для обращения к функции класса без создания объекта этого класса
            if (!baseinit) {           // если объект класса не создан, то создаем, иначе возвращаем уже созданный
                baseinit = new A(i);
            };
            return baseinit;
        }    

        void print() {
            cout << this -> a << endl;
        }

};

A* A::baseinit = nullptr;               //иницилизиуруем пустой объект который потом проверяем на существование, чтобы не создавать нвоые а ссылаться на него же


int main () {
    A* a1 = A::init(3495);
    a1 -> print();

    A* a2 = A::init(10);
    a2 -> print();

    A* a3 = a2;
    a3 -> print();
}
