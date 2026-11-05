#include <iostream>
using namespace std;

class Shape {
public:
    virtual float area() = 0; // Pure virtual function
};

class Circle : public Shape {
private:
    float radius;
public:
    Circle(float r) { 
        radius = r; 
    }
    float area() override { 
        return 3.14159 * radius * radius; 
    }
};

class Rectangle : public Shape {
private:
    float length, breadth;
public:
    Rectangle(float l, float b) { 
        length = l; 
        breadth = b; 
    }
    float area() override { 
        return length * breadth; 
    }
};

class Triangle : public Shape {
private:
    float base, height;
public:
    Triangle(float b, float h) { 
        base = b; 
        height = h; 
    }:
    float area() override { 
        return 0.5 * base * height; 
    }
};

int main() {
    float r, length, breadth, base, height;

    cout << "Enter radius of the circle: ";
    cin >> r;
    Circle c(r);

    cout << "Enter length and breadth of the rectangle: ";
    cin >> length >> breadth;
    Rectangle rect(length, breadth);

    cout << "Enter base and height of the triangle: ";
    cin >> base >> height;
    Triangle t(base, height);

    Shape *ptr;

    ptr = &c;
    cout << "Area of Circle: " << ptr->area() << endl;

    ptr = &rect;
    cout << "Area of Rectangle: " << ptr->area() << endl;

    ptr = &t;
    cout << "Area of Triangle: " << ptr->area() << endl;

    return 0;
}
