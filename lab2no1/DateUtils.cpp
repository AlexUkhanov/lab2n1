#include "DateUtils.h"

//Проверка на високосность
bool Date::IsLeap(int year)
{
	if (year % 4)
		return false;
	if (year % 100)
		return true;
	return !(year % 400);
}

//Проверка даты на корректность
bool Date::CorrectDate(int day, int month, int year)
{
	if ((month == 2 && day > 29 && IsLeap(year)) || (month == 2 && day > 28 && !IsLeap(year)))
	{
		cout<<"Wrong number of days in February"<<endl;
		return false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			cout << "Wrong number of days in a month" <<endl;
			return false;
		}
	}
	return true;
}

//Конструктор
Date::Date()
{
	day = 1;
	month = 1;
	year = 1970;	
}

//Ввод даты
void Date::InputDate()
{
	bool Correct = true; // корректна ли введенная дата
	do
	{
		day = InputNumber(1, 31, "Date entry:\nEnter the day (1-31): ");
		month = InputNumber(1, 12, "Enter the month's number (1-12): ");
		year = InputNumber(1970, 2100, "Enter the year (1970-2100): ");
		Correct = CorrectDate(day, month, year);
	} while (!Correct);  // повторять ввод пока не корректная дата
}

//Преобразование в строку
string Date::ToString()
{
	return (to_string(day) + '.' + to_string(month) + '.' + to_string(year));
}

//Перегруженный оператор равенства
bool Date::operator == (const Date &d)
{
	return ((day == d.day) && (month == d.month) && (year == d.year));
}

//Перегруженный оператор больше
bool Date::operator > (const Date &d)
{
	return ((year > d.year) || ((year == d.year) && (month > d.month)) || ((year == d.year) && (month == d.month) && (day>d.day)));
}

//Перегруженный оператор меньше
bool Date::operator < (const Date &d)
{
	return ((year < d.year) || ((year == d.year) && (month < d.month)) || ((year == d.year) && (month == d.month) && (day<d.day)));
}

//Перегруженный оператор присваивания
Date& Date::operator = (const Date d)
{
	day = d.day;
	month = d.month;
	year = d.year;
	return(*this);
}

//Преобразование даты из строки вида day.month.year в тип дата
Date DateFromString(string str)
{
	Date result;
	try
	{
		istringstream is(str);
		string s;
		if (getline(is, s, '.'))
			result.day = atoi(s.c_str());
		if (getline(is, s, '.'))
			result.month = atoi(s.c_str());
		if (getline(is, s, '.'))
			result.year = atoi(s.c_str());
	}
	catch (...)
	{
		cout << "Error of reading date!" << endl;
	}
	return result;
}
