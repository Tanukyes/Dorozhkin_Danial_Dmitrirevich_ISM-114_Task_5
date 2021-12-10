#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class MyExcept1 {};

class MyExcept2
{
	string msg;
public:
	MyExcept2(const string& s) : msg(s) {}
	const char* message() const { return msg.c_str(); }
};

class MyExcept3 : public invalid_argument
{
	bool num;
public:
	MyExcept3(const string msg, bool n) : invalid_argument(msg), num(n) {}
	bool arg() const { return num; }
};

bool isLeap1(int year)
{
	if (year < 0 || cin.fail())
		cerr << "Произошло исключение в функции isLeap1" << endl;
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

bool isLeap2(int year) throw(int)
{
	if (year < 0)
		throw - 1;
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

bool isLeap3(int year) throw(invalid_argument)
{
	if (year < 0)
		throw invalid_argument("Год не может быть отрицательным!");
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;;
}

bool isLeap4_1(int year) throw(MyExcept1)
{
	if (year < 0)
		throw MyExcept1();
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

bool isLeap4_2(int year) throw(MyExcept2)
{
	if (year < 0)
		throw MyExcept2("Год не может быть отрицательным!");
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

bool isLeap4_3(int year) throw(MyExcept3)
{
	if (year < 0)
		throw MyExcept3("Неверный аргумент ", year);
	return year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

void launcher(bool (*func)(int))
{
	int year;
	cout << "Введите год: ";
	cin >> year;
	cout << "Год " << year << (func(year) ? " " : " не ") << "високосный!" << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");

	try
	{
		launcher(isLeap1);
	}

	catch (...)
	{
		cout << "Произошло исключение в функции isLeap1" << endl;
	}

	try
	{
		launcher(isLeap2);
	}

	catch (int)
	{
		cout << "Произошло исключение в функции isLeap2" << endl;
	}

	try
	{
		launcher(isLeap3);
	}

	catch (invalid_argument& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		launcher(isLeap4_1);
	}

	catch (MyExcept1)
	{
		cout << "Произошло исключение MyExcept1 в функции isLeap4_1" << endl;
	}

	try
	{
		launcher(isLeap4_2);
	}
	catch (MyExcept2& e)
	{
		cout << e.message() << endl;
	}

	try
	{
		launcher(isLeap4_3);
	}

	catch (MyExcept3& e)
	{
		cout << e.what() << " " << e.arg() << endl;
	}
}
