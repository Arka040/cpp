#include <iostream>

using namespace std;

class Arr {
    int *arr;
    int size;
    public:
        Arr(int s, int date=0): size(s) {
            arr = new int[s];
            for(int i = 0; i < size; arr[i++] = date);
        }

        ~Arr() {
            delete []arr;
        }

        int & operator[] (int num){
            return arr[num];
        }

        friend ostream& operator<< (ostream& out, const Arr& array);
        friend Arr operator| (Arr array, int num);
        friend Arr operator| (Arr array1, Arr array2);
        friend Arr operator- (Arr array);

        Arr& operator|= (int num) {
            for (int i = 0; i < this -> size; i++) {
                this -> arr[i] |= num;
            }
            return *this;
        }

        Arr& operator= (const Arr& array) {
            if (this == &array) {
                return *this;
            }
            delete []arr;
            size = array.size;
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = array.arr[i];
            }
            return *this;
        }

        Arr& operator= (Arr&& array) {
            if (this == &array) {
                return *this;
            }
            delete []arr;
            size = array.size;
            arr = array.arr;
            array.size = 0;
            array.arr = nullptr;
            // cout << "ogeiwjgw" << endl;
            return *this;
        }

        Arr(const Arr& array) {
            size = array.size;
            arr = new int[size];
            cout << "ogeiwjgw" << endl;

            for (int i = 0; i < size; i++) {
                arr[i] = array.arr[i];
            }
        }
};

ostream& operator<< (ostream& out, const Arr& array){
    for (int i = 0; i < array.size; i++) {
        cout << array.arr[i];
    }
    cout << endl;
    return out;
}

Arr operator| (Arr array, int num) {
    Arr A(array.size);
    for (int i = 0; i < array.size; i++) {
        A.arr[i] = array.arr[i] | num;
    }
    return A;
}

Arr operator| (Arr array1, Arr array2) {
    Arr A(min(array1.size, array2.size));
    for (int i = 0; i < A.size; i++) {
        A.arr[i] = array1.arr[i] | array2.arr[i];
    }
    return A;
}

Arr operator- (Arr array){
    Arr A(array.size);
    for (int i = 0; i < A.size; i++) {
        A.arr[i] = -array.arr[i];
    }
    return A;
}

int main() {
    Arr a1(15), a2(20, 5), a3(30, 3);
    const Arr a4(5);
    cout << a1 << a2 << a3 << a4;
    a2 = a2 | 2; 
    a2 |= 1;
    a3 = (-a2) | (-a4);
    a3[3] = 10;
    a1 = a4 | a3;
    cout << a1 << a2 << a3 << a4;
    return 0;
}