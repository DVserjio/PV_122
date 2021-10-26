﻿#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//				Constructors:
	Point()
	{
		x = 0;
		y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//				Operators:
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}

	//				Methods:
	double distance(const Point& other)
	{
		/*double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		return distance;*/
		return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
		//pow - возведение в степень
		//sqrt(Square Root) - Квадратный корень
	}
	void print()const
	{
		cout << "X = " << x << "\t" << "Y = " << y << endl;
	}
};

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
	return distance;
}

#define delimiter "\n---------------------------------------------------------\n"
//#define STRUCT_POINT
//#define DISTANCE
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Объявление переменной 'A' типа 'Point'
				//Объявление экземпляра 'A' структуры 'Point'
				//Объявление объекта 'A' структуры 'Point'
				//Создание объекта 'A' структуры 'Point'
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef DISTANCE
	Point A;	//Default constructor
//cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B;
	B.set_x(3);
	B.set_y(4);
	cout << B.get_x() << "\t" << B.get_y() << endl;
	cout << "Размер объекта: " << sizeof(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки A до точки B: " << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки B до точки A: " << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками A и B:   " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками B и A:   " << distance(B, A) << endl;
	cout << delimiter << endl;
#endif // DISTANCE

#ifdef CONSTRUCTORS_CHECK
	Point A;	//Default constructor
	A.print();

	Point B(2, 3);
	B.print();

	Point C = B;//Copy constructor
	C.print();

	Point D;	//Default constructor
	D = B;		//Copy assignment - оператор присваивания
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << delimiter << endl;
	A = B = C = Point(2, 3);	
	//Point(2,3) - явный вызов конструктора. 
	//Таким образом создается временный безымянный объект,
	//который существует только в пределах выражения,
	//и удаляется после завершения выражения.
	cout << delimiter << endl;
	A.print();
	B.print();
	C.print();
#endif

	Point A(2, 3);
	Point B(3, 4);
	Point C = A + B;
}

/*
----------------------------------------------------
.  - Оператор прямого доступа (Point operator)
-> - Оператор косвенного доступа (Arrow operator)
----------------------------------------------------
*/

/*
----------------------------------------------------
Constructor - это метод, который создает объект.
~Destructor - это метод, который удаляет объект по истечении его времени жизни.

Default constructor
----------------------------------------------------
*/

/*
----------------------------------------------------
			OPERATORS OVERLOADING RULES
1. Перегрузить можно только существующие операторы;
	+  - перегружается;
	++ - перегружается;
	*  - перегружается;
	** - НЕ перегружается;
2. НЕ все существующие операторы можно перегрузить.
   НЕ перегружаются:
	?: - Ternary;
	:: - Scope operator (Оператор разрешения видимости)
	.  - Point operator;
	.* - Pointer to member selection;
	#
	##
3. Перегруженные операторы сохраняют приоритет;
4. Переопределить поведение операторов со встроенными типами невозможно;
----------------------------------------------------
*/