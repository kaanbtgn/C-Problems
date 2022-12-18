#include <iostream>
#include <vector>
using namespace std;

class Shape {
    friend ostream& operator<<(ostream&, Shape&);
public:
    Shape(double = 0.0, double = 0.0);
    double get_centerX() const;
    double get_centerY() const;
    virtual void print() const = 0;
protected:
    double xcenter;
    double ycenter; 
};
Shape::Shape(double x, double y)
{    xcenter = x;
     ycenter = y;
}
double Shape::get_centerX() const
{
    return xcenter;
}
double Shape::get_centerY() const
{
    return ycenter;
}
ostream& operator<<(ostream& out, Shape& s)
{
    s.print();
    return out;
}
class TwoDimensionalShape : public Shape
{
public:
    TwoDimensionalShape(double x, double y) : Shape(x, y) { }
    virtual double get_area() const = 0;
};
class ThreeDimensionalShape : public Shape
{
public:
    ThreeDimensionalShape(double x, double y) : Shape(x, y) { }
    virtual double get_area() const = 0;
    virtual double get_volume() const = 0;
};
class Circle : public TwoDimensionalShape
{
public:
    Circle(double = 0.0, double = 0.0, double = 0.0);
    virtual double get_radius() const;
    virtual double get_area() const;
    void print() const;
private:
    double radius;
};
Circle::Circle(double r, double x, double y)
    : TwoDimensionalShape(x, y)
{
    radius = ((r > 0.0) ? r : 0.0);
}
double Circle::get_radius() const
{
    return radius;
}
double Circle::get_area() const
{
    return 3.14159 * radius * radius;
}

void Circle::print() const
{
    cout << "Circle with radius " << radius << "; center at ("
        << xcenter << ", " << ycenter << ")";
}
class Cube : public ThreeDimensionalShape
{
public:
    Cube(double = 0.0, double = 0.0, double = 0.0);

    virtual double get_area() const;
    virtual double get_volume() const;
    double getSideLength() const;
    void print() const;
private:
    double sideLength;
};
Cube::Cube(double s, double x, double y)
    : ThreeDimensionalShape(x, y)
{
    sideLength = ((s > 0.0) ? s : 0.0);
}
double Cube::get_area() const
{
    return 6 * sideLength * sideLength;
}
double Cube::get_volume() const
{
    return sideLength * sideLength * sideLength;
}
double Cube::getSideLength() const
{
    return sideLength;
} 
void Cube::print() const
{
    cout << "Cube with side length " << sideLength << "; center at ("
        << xcenter << ", " << ycenter << ")";
} 
int main(){
    vector < Shape* > shapes(2);
    shapes[0] = new Circle(3.5, 6, 9);
    shapes[1] = new Cube(2.2);
    for (int i = 0; i < 2; i++)
    {
        cout << *shapes[i] << endl;
        TwoDimensionalShape* twoDimensionalShapePtr =
            dynamic_cast <TwoDimensionalShape*> (shapes[i]);

        if (twoDimensionalShapePtr != 0) {
            cout << "Area: " << twoDimensionalShapePtr->get_area() << endl;
        }
        
        ThreeDimensionalShape* threeDimensionalShapePtr =
            dynamic_cast <ThreeDimensionalShape*> (shapes[i]);

        if (threeDimensionalShapePtr != 0) {
            cout << "Area: " << threeDimensionalShapePtr->get_area()
                << "\nVolume: " << threeDimensionalShapePtr->get_volume()
                << endl;
        }

        cout << endl;
    }
}
