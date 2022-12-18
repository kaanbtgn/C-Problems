#include <iostream>
#include "Complex.h"
using namespace std;

class Complex
{
public:
	Complex(double = 0.0, double = 0.0);
	Complex add(const Complex&);
	Complex subtract(const Complex&);
	void printComplex();
	void setComplexNumber(double, double);
	double calcabs();
private:
	double realPart;
	double imaginaryPart;
	double mutlak1();
};

Complex::Complex(double real, double imaginary)
{
	setComplexNumber(real, imaginary);
}
Complex Complex::add(const Complex& righthand)
{
	return Complex(
		realPart + righthand.realPart, imaginaryPart + righthand.imaginaryPart);
}
Complex Complex::subtract(const Complex& rightHand)
{
	return Complex(
		realPart - rightHand.realPart, imaginaryPart - rightHand.imaginaryPart);
}
void Complex::printComplex()
{
	cout << '(' << realPart << "," << imaginaryPart << ')';
}
void Complex::setComplexNumber(double real, double imaginer)
{
	realPart = real;
	imaginaryPart = imaginer;
}
double Complex::calcabs()
{
	return mutlak1();
}
double Complex::mutlak1()
{
	return realPart * realPart + imaginaryPart * imaginaryPart;
}

int main()
{
	int real, imaginer,real_2,imaginer_2;
	cout << "Enter Real part and Imaginary Part of your First Complex Number" << endl;
	cin >> real >> imaginer;
	cout << "Enter Real part and Imaginary Part of your Second Complex Number" << endl;
	cin >> real_2 >> imaginer_2;
	Complex a(real,imaginer), b(real_2,imaginer_2), c;
	a.printComplex();
	cout << " + ";
	b.printComplex(); 
	cout << " = ";
	c = a.add(b);
	c.printComplex();
	cout << '\n';
	a.setComplexNumber(10, 1);
	b.setComplexNumber(11, 5);
	a.printComplex();
	cout << " - ";
	b.printComplex();
	cout << " = ";
	c = a.subtract(b);
	c.printComplex();
	cout << endl;
	cout << "Value of c is equal to " << c.calcabs() << endl;
}