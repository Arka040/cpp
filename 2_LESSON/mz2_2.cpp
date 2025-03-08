#include <iostream>
#include <string>

using namespace std;

class A {
    int a;
    ~A(){};
    A (const A & cop) {
        this -> a = cop.a;
    };
    public:
        A(int i = 0) : a(i) {};

        void del() {
            cout << "delete" << endl;
            this -> ~A();
        }

        void print() {
            cout << this -> a << endl;
        }

};


int main ()  {
    // A* a1 = A::init(3495);
    // a1 -> print();

    int N = 4;

    // A* arr[sizeof(A) * 15];

    char *memory = new char[N*sizeof(A)];
    A *arr[N];
    for (int i = 0; i < N; i++) { 
        arr[i] = new (&memory[i*sizeof(A)]) A(i); 
    }
    for (int i = 0; i < N; i++) { 
        arr[i]->print();
    }
    for (int i = 0; i < N; i++) { 
        arr[i]->del();
    }
    delete []memory;


    // for (int i = 0; i < 15; i++) {
    //     arr[i] = A(i + 100);
    // }

    // for (int i = 0; i < 15; i++) {
    //     arr[i].print();
    // }

    // for (int i = 0; i < 15; i++) {
    //     arr[i].del();
    // }

    // a1 -> del();

    // a1 -> print();

    // A* a2 = A::init(10);
    // a2 -> print();

    // A* a3 = a2;
    // a2 -> print();
}
