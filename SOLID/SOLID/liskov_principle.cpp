/*
Liskov Substitution Principle (LSP):

LSP states that objects of a base class should be able to be replaced with objects of a derived class without affecting the correctness of the program.
In simple words, derived classes must be substitutable for their base classes.

Below is a simple, practical C++23 example with shape area calculation.
*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
// Base class: Shape
class Shape {
public:
    // All shapes must implement this
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

// Derived class: Rectangle
class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

// Derived class: Circle
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// client code: uses only the base class interface
void printShapeAreas(const vector<unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        cout << "Area: " << shape->area() << '\n';
    }
}

int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Rectangle>(3, 4)); // 3x4 rectangle
    shapes.push_back(make_unique<Circle>(5));       // circle radius 5

    // LSP in action: we treat Rectangles and Circles as Shapes
    printShapeAreas(shapes);

    // No need to know what kind of shape each is, as long as all correctly implement area()
    return 0;
}

/*
Key points to understand:
- All derived classes (Rectangle, Circle) implement Shape's interface.
- You can substitute Rectangle or Circle wherever Shape is expected.
- Client code (printShapeAreas) works correctly without knowing about derived classes at all.

This is the essence of Liskov Substitution Principle.
*/