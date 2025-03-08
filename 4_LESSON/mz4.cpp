#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename T> 
void print_forward(const T& object) {
    // typename T::const_iterator iter = object.begin();
    auto iter = object.begin();

    for (iter; iter != object.end(); iter++) {
        cout << *iter << ' ';
    }
    cout << endl;
}

template<typename T>
void print_backwards(const T& object) {
    // typename T::const_reverse_iterator iter = object.rbegin();
    // auto iter = object.rbegin();

    for (auto iter :object) {
        cout << iter << ' ';
    }
    cout << endl;
}

template<typename T>
void join(vector<T>& v, list<T>& l){
    int numerate = 1;
    while(1) {
        if (numerate <= v.size()){
            if (l.size() >= 1) {
                v.insert(v.begin() + numerate, l.front());
                l.pop_front();
            } else {
                v.insert(v.begin() + numerate, 0);
            }
            if (l.size() != 0){
                l.pop_front();
            }
            numerate += 3;
        }
        else {
            break;
        }
    }
}

template<typename T>
void del(T& object, int n) {
    if (n >= object.size()) {
        throw "the number is bigger than lenght";
    }
    n--;
    // typename T::iterator it = object.begin();
    auto it = object.begin();

    for (int i = 1; i < object.size(); i++) {
        it++;
        if (i % n == 0) {
            it = object.erase(it);
            continue;
        }
    }
}


int main () {
    vector <int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    const vector<int>  v2 = {1, 2, 3, 4, 5, 6, 7};
    list<int> l = {10, 11, 12, 13, 14, 15, 16, 17, 18};
    try{
        del(l, 3);
    } catch (const char* err) {
        cout << err << endl;
    }

    print_forward(l);
    print_forward(v);
    join(v, l);
    print_forward(v);
    print_backwards(v);

}