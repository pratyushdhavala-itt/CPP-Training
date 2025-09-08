#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    std::string m_name;
public:
    Shape(const std::string& name) : m_name{name} {
        cout << "Shape constructor" << endl;
    }

    const std::string& getName() const { return m_name; }
    
    virtual void printArea() const {
        std::cout << "The Shape class does not know how to calculate area.\n";
    }
};


class Circle : public Shape {
private:
    double m_radius;
public:
    Circle(double radius) : Shape("Circle"), m_radius{radius} {
        cout << "Circle constructor" << endl;
    }

    double getRadius() const { return m_radius; }

    virtual void printArea() const {
        int area = 3.14 * m_radius * m_radius;
        std::cout << "Area of Circle is " << area << std::endl;
    }   

};


class Square : public Shape {
private:
    double m_side;
public:
    virtual Square(double side) : Shape("Square"), m_side{side} {
        cout << "Square constructor" << endl;
    }

    virtual void printArea() const {
        int area = m_side * m_side;
        std::cout << "Area of Square is " << area << std::endl;
    }   
};


void report(const Shape& s) {
    std::cout << "This object is a " << s.getName() << ".\n";

    s.printArea();

}

int main() {
    Circle circle(5.0);
    Square square(10.0);

    report(circle); 
    std::cout << '\n';
    report(square);

    return 0;
}