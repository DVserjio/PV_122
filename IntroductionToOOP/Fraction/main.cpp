﻿//Fraction - описываем простую дробь
#include<iostream>
#pragma warning(disable:4326)
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);

class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//					Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		//Single-argument constructor - Конструктор с одним параметром.
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgConstructor:" << this << endl;
	}

	Fraction(double decimal)
	{
		decimal += 1e-11;
		integer = decimal; //Сохраняем целую часть десятичной дроби
		decimal -= integer; //Убираем целую часть из десятичной дроби
		denominator = 1e+9;  //1*10 в девятой степени
		numerator = decimal * denominator; //Умножаем дробную часть десятичной дроби на миллиард
		// и таким образом вся дробная часть переходит в целую часть. И сохраняем ее в числителе.
		reduce();
		cout << "doubleConstructor:\t" << this << endl;
	}

	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor\t" << this << endl;
	}

	//				Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//  Increment/Decrement
	Fraction& operator++()  //Prefix Increment
	{
		to_proper();
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this; //Сохраняем текущее состояние объекта
		to_proper();
		integer++;
		return old;
	}

	//   Type-cast operators
	explicit operator int()
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//				Methods:
	Fraction& to_proper()
	{
		//Переводит дробь в правильную - выделяет целую часть:
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//Переводит дробь в НЕправильную - интегрирует целую часть в числитель:
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& inverted()
	{
		to_improper();
		int buffer = numerator;
		numerator = denominator;
		denominator = buffer;
		return *this;
	}
	Fraction reduce()
	{
		//Сокращает дробь:
	//https://www.webmath.ru/poleznoe/formules_12_7.php
		if (numerator == 0)
		{
			denominator = 1;
			return *this;
		}
		int more;  //Большее значение
		int less;  //Меньшее значение
		int rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return to_proper();
	}
	void print()
	{
		if (integer)cout << integer;	//Если есть целая часть, выводим ее на экран
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//Fraction result
	//(
	//	left.get_numerator()*right.get_numerator(),
	//	left.get_denominator()*right.get_denominator()
	//);
	////result.set_numerator(left.get_numerator() * right.get_numerator());
	////result.set_denominator(left.get_denominator() * right.get_denominator());
	//result.to_proper();
	//return result;

	//Явно вызываем конструктор прямо в return-e.
	//Этот конструктор создает ВРЕМЕННЫЙ БЕЗЫМЯННЫЙ ОБЪЕКТ,
	//который return сразу ЖЕ возвращает на место вызова:
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}

//   Comparison operators:
bool operator==(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	/*if (left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator())
		return true;
	else
		return false;*/
		//return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
	return
		left.to_improper().get_numerator() * right.get_denominator() ==
		right.to_improper().get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	return
		left.to_improper().get_numerator() * right.get_denominator() >
		right.to_improper().get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	return
		left.to_improper().get_numerator() * right.get_denominator() <
		right.to_improper().get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	//return left > right || left == right;
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	//return left < right || left == right;
	return !(left > right);
}
ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();	//Если есть целая часть, выводим ее на экран
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}

istream& operator >> (istream& is, Fraction& obj)
{
	const int SIZE = 50;
	char buffer[SIZE] = {};
	char delimiters[] = " ()/";
	//is >> buffer;
	is.getline(buffer, SIZE);
	char* value[3] = {};
	int n = 0;
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		value[n++] = pch;
	}
	//for (int i = 0; i < n; i++)
	//{
	//	cout << value[i] << "\t";
	//}
	///*cout << endl;*/
	switch (n)
	{
	case 1: obj.set_integer(atoi(value[0])); break;
	case 2:
		obj.set_numerator(atoi(value[0]));
		obj.set_denominator(atoi(value[1]));
		break;
	case 3:
		obj.set_integer(atoi(value[0]));
		obj.set_numerator(atoi(value[1]));
		obj.set_denominator(atoi(value[2]));
		return is;
	}
}


//#define CONSTRUCTORS_CHECK
//#define OSTREAM_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPARISON_OPERATORS
//#define ISTREAM_OPERATOR_CHECK
//#define TYPE_CONVERSION_BASICS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();
	Fraction B = 5;	//Single-argument constructor (Конструктор с одним параметром).
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OSTREAM_CHECK
	Fraction A(14, 4);
	A.to_proper();
	A.print();
	A.to_improper();
	A.print();
#endif // OSTREAM_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	int a = 2;
	int b = 3;
	int c = a * b;

	Fraction A(1, 2, 3);
	Fraction B(2, 4, 5);
	cout << A << endl;
	cout << B << endl;
	Fraction C = A * B;
	cout << C << endl;
	cout << A / B << endl;
	A *= B;
	cout << A << endl;
	A /= B;
	cout << A << endl;
	cout << ++A << endl;
	A = ++B;
	cout << A << endl;
	cout << B << endl;
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef COMPARISON_OPERATORS
	Fraction A(1, 5, 10);
	Fraction B(1, 100, 220);
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	cout << (A > B) << endl;
	cout << (A < B) << endl;
#endif // COMPARISON_OPERATORS

#ifdef ISTREAM_OPERATOR_CHECK
	Fraction A;
	cout << "Введите дробь: ";
	cin >> A;
	cout << A << endl;
#endif // ISTREAM_OPERATOR_CHECK

#ifdef TYPE_CONVERSION_BASICS
	int a = 2;    //No conversions
	double b = 3; //Conversion from int to double
				  //            from less to more
	int c = b;    //Coversion from double to int without data loss
				  //           from more to less withou data loss
	int d = 4.5;   //Conversion from double to int 
				   //           from more to less with data loss
	cout << d << endl;
#endif // TYPE_CONVERSION_BASICS

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	double a = 2; //From int to double (from less to more)
	Fraction A = (Fraction)5; //From int to Fraction (from less to more)
	cout << A << endl;
	cout << "\n----------------------------------------------\n";
	Fraction B;  //Default constructor
	cout << "\n----------------------------------------------\n";
	B = Fraction(8);   //Conversion from int to Fraction
	cout << "\n----------------------------------------------\n";
	cout << B << endl;

	Fraction C(12); //explicit конструктор можно вызвать так и нельзя вызвать так: Fraction C=12;
	cout << C << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	//Type-cast operators
/*
------------------------------

operators type()
{
	//conversion is here
}

------------------------------
*/
	Fraction A(2, 3, 4);
	int a = (int)A;
	cout << A << endl;
	cout << a << endl;
	double b = (double)A;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

	Fraction A = 2.75;
	cout << A << endl;
	Fraction B(2, 76, 100);
	cout << B << endl;
	cout << (A == B) << endl;

	Fraction C(1, 3);
	cout << C*3 << endl;
}