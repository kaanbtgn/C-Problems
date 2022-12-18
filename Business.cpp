#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class Employee {
public:
    Employee(const char*, const char*);
    void print() const;
    ~Employee();
private:
    char* firstName;
    char* lastName;
};

class HourlyWorker : public Employee {
public:
    HourlyWorker(const char*, const char*, double, double);
    double getPay() const;
    void print() const;
private:
    double wage;
    double hours;
};

Employee::Employee(const char* first, const char* last)
{
    firstName = new char[strlen(first) + 1];
    for (int i = 0; i <= strlen(first); i++)
        firstName[i] = first[i];

    lastName = new char[strlen(last) + 1];
    for (int i = 0; i <= strlen(first); i++)
        lastName[i] = last[i];
}
void Employee::print() const
{
    cout << firstName << ' ' << lastName;
}
Employee::~Employee()
{
    delete[] firstName;
    delete[] lastName;
}
HourlyWorker::HourlyWorker(const char* first,
    const char* last, double initHours, double initWage)
    : Employee(first, last)
{
    hours = initHours;
    wage = initWage;
}
double HourlyWorker::getPay() const { return wage * hours; }

void HourlyWorker::print() const
{
    cout << "HourlyWorker::print() is executing\n\n";
    Employee::print();
    cout << " is an hourly worker with pay of $"<< getPay() << endl;
}
int main()
{
	HourlyWorker g("Thor", "Odinson", 9999999999.0, 999999990.00);
	g.print();
	HourlyWorker i("Tony", "Stark", 999.0, 9999.00);
    i.print();
	HourlyWorker j("Steve", "Rogers", 99.0, 999.00);
	j.print();
	HourlyWorker k("Bruce", "Banner", 99.0, 999.00);
	k.print();
	HourlyWorker l("Natasha", "Romanoff", 9.0, 99.00);
	l.print();
	HourlyWorker m("Clint", "Barton", 9.0, 999.00);
	m.print();
	HourlyWorker n("Wanda", "Maximoff", 9999.0, 9999.00);
	n.print();
	HourlyWorker o("Peter", "Parker", 99.0, 999.00);
	o.print();
	HourlyWorker p("Scott", "Lang", 9.0, 99.00);
	p.print();
	HourlyWorker q("T'Challa", "Black Panther", 9999999.0, 99999999.00);
	q.print();
	HourlyWorker r("Stephen", "Strange", 9999999.0, 99999999.00);
	r.print();
	HourlyWorker s("Carol", "Danvers", 999999.0, 99999999.00);
	s.print();
	HourlyWorker t("Sam", "Wilson", 9.0, 9.00);
	t.print();
	HourlyWorker u("Bucky", "Barnes", 99.0, 999.00);
	u.print();
	HourlyWorker v("Nebula", "Odinson", 9999.0, 999999.00);
	v.print();
	HourlyWorker w("Gamora", "Zehar", 99.0, 99.00);
	w.print();
	HourlyWorker x("Rocket", "Raccoon", 99.0, 99.00);
	x.print();
	HourlyWorker y("Groot", "Tree", 659.0, 999.00);
	y.print();
	HourlyWorker z("Drax", "The Destroyer", 99.0, 99.00);
	z.print();
	HourlyWorker a("Mantis", "Odinson", 9999999.0, 9999999.00);
	a.print();
}