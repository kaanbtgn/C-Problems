#include <iostream>
using namespace std;
class Shape {
 public:
 virtual double area() const { return 0.0; }
virtual void printShapeName() const = 0;
virtual void print() const = 0;
 };

 class Point : public Shape {
public:
Point( int = 0, int = 0 );
void setPoint( int, int );
int getX() const { return x; }
int getY() const { return y; }

virtual void printShapeName() const { cout << "Point: "; }
virtual void print() const;
private:
int x, y;
};

Point::Point( int a, int b ) { setPoint( a, b ); }

 void Point::setPoint( int a, int b )
 {
 x = a;
 y = b;
 }

void Point::print() const
 { cout << '[' << x << ", " << y << ']'; }
class Circle : public Point {
public:
 Circle( double r = 0.0, int x = 0, int y = 0 );
  void setRadius( double );
 double getRadius() const;
 virtual double area() const;
 virtual void printShapeName() const { cout << "Circle: "; }
virtual void print() const;
private:
double radius;
 };

 Circle::Circle( double r, int a, int b )
: Point( a, b )
{ setRadius( r ); }
void Circle::setRadius( double r ) { radius = r > 0 ? r : 0; }

 double Circle::getRadius() const { return radius; }

double Circle::area() const
 { return 3.14159 * radius * radius; }

 void Circle::print() const
 {
 Point::print();
cout << "; Radius = " << radius;
}
 
int main()
{
 Point point( 7, 11 );
 Circle circle( 3.5, 22, 8 );
 point.printShapeName();
 point.print();
 cout << '\n';
 circle.printShapeName();
 circle.print();
 cout << '\n';
 cout << "\n\n";
 Shape *arrayOfShapes[ 2 ];
 arrayOfShapes[ 0 ] = &point;
 arrayOfShapes[ 1 ] = &circle;
 for ( int i = 0; i < 2; i++ )
 virtualViaPointer( arrayOfShapes[ i ] );
return 0;
}
void virtualViaPointer( const Shape *baseClassPtr )
{
 baseClassPtr->printShapeName();
 baseClassPtr->print();
 cout << "\nArea = " << baseClassPtr->area()<< "\n\n";
}
