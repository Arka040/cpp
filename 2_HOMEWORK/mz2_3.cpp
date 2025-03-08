#include <iostream>
#include <cstring>
using namespace std;


class BinaryNumber {

    string number;
    int len;

    public:
        BinaryNumber(const string &s) : number(s), len(s.length()) {};

        operator string () const {      // перегружаем оператор string (возвращаем строку бинарного числа)
            return number;
        }; // преобразует объект класса в стринг

        int string_to_int() {;
            int numer = 0;
            for (int i = 0; i < this -> len; i++) {
                numer = numer * 2 + this -> number[i] - '0';
            }
            return numer;
        }

        string from_int_to_string(int num) {
            string binary ("");
            int mask = 1;
            for(int i = 0; i < 31; i++)
            {
                if((mask&num) >= 1)
                    binary = "1"+binary;
                else
                    binary = "0"+binary;
                mask<<=1;
            }
            return binary;
        }

        string remove_zeros(string num) {
            int flag = 0;
            string without_zeros ("");
            for (int i = 0; i < 31; i++) {
                if ((!flag)) {
                    if (num[i] == '1') {
                        flag++;
                        without_zeros = without_zeros + num[i];
                    }
                }
                else {
                    without_zeros = without_zeros + num[i];
                }

            }
            return without_zeros;
        }

        const BinaryNumber &operator++(int) {
            this -> number = remove_zeros(from_int_to_string(string_to_int() + 1));
            return *this;
        }; // увеличивает на 1


};


int main () {
    string bin_str;
    cout << "input bin number: ";
    cin >> bin_str;

    BinaryNumber num(bin_str);

    num++;
    cout << string(num) << endl;

}

