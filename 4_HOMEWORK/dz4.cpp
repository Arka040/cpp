#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Figure {
    string namee;
    public:
        Figure(const string name): namee(name) {};
        virtual string name() const {
            return namee;
        };
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
};

class Square : public Figure {
    int side;
    public:
        Square(int side): Figure("Square"), side(side) {};
        double area() const override {
            return side * side;
        }
        double perimeter() const override {
            return side * 4;
        }
};

class Rectangle : public Figure {
    int width, height;
    public:
        Rectangle(int w, int h): Figure("Reactangle"), width(w), height(h) {};
        double area() const override {
            return width * height;
        }
        double perimeter() const override {
            return (width + height) * 2;
        }
};

class Triangle : public Figure {
    int a, b, c;
    public:
        Triangle(int a, int b, int c): Figure("Triangle"), a(a), b(b), c(c) {};
        double area() const override {
            double p = (a + b + c) / 2.0;
		    return sqrt(p * (p - a) * (p - b) * (p - c));
        }
        double perimeter() const override {
            return a + b + c;
        }
};

class Working {
    Figure* f[5];
    int n;
    public:
        Working(): n(0) {};
        void addFigure(Figure* item) {
            f[n] = item;
            n++;
        }
        void print_areas() {
            for (int i = 0; i < n; i++) {
                cout << "Area of " << f[i] -> name() <<  " is: " << f[i] -> area() << endl;
            }
        }
        void print_perimeters() {
            for (int i = 0; i < n; i++) {
                cout << "Perimeter of " << f[i] -> name() <<  " is: " << f[i] -> perimeter() << endl;
            }
        }
        void print_all() {
            for (int i = 0; i < n; i++) {
                cout << "Area of " << f[i] -> name() <<  " is: " << f[i] -> area() << "    Perimeter of " << f[i] -> name() <<  " is: " << f[i] -> perimeter() << endl;
            }
        }
};


int main() {
    Square s(5);
    Rectangle r(2, 3);
    Triangle t(5, 6, 7);

    Working w;
    w.addFigure(&s);
    w.addFigure(&r);
    w.addFigure(&t);
    w.print_all();
}