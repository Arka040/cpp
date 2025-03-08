#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

class func {
    public:
        template<typename T>
        void operator()(vector<T> &object) {
            reverse(object.begin(), object.end());
        }

        template<typename T>
        void operator()(list<T> &object) {
            reverse(object.begin(), object.end());
        }

        void operator()(string &object) {
            reverse(object.begin(), object.end());
        }

};


int main () {
    func f;
    vector<int> v = {1, 2, 3, 4};
    list<int> l = {5, 6, 7, 8};
    string s = "Arkadiy";
    cout << "--------------" << endl;
    f(v);
    for (auto &i: v) {
        cout << i << endl;
    }
    cout << "--------------" << endl;

    f(l);
    for (auto &i: l) {
        cout << i << endl;
    }
    cout << "--------------" << endl;

    f(s);
    cout << s << endl;
    // for (auto &i: s) {
        // cout << i << endl;
    // }

    return 0;
}
