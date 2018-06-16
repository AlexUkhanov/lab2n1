#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "HelpUtils.h"

class Date
{
	//Проверка на високосность
	bool IsLeap(int year);
	//Проверка даты на корректность
	bool CorrectDate(int day, int month, int year);

public:
	int day;
	int month;
	int year;

	//Конструктор
	Date();
	//Ввод даты
	void InputDate();
	//Преобразование в строку
	string ToString();
	//Перегруженный оператор равенства
	bool operator == (const Date &d);
	//Перегруженный оператор больше
	bool operator > (const Date &d);
	//Перегруженный оператор меньше
	bool operator < (const Date &d);
	//Перегруженный оператор присванивания
	Date& operator = (const Date d);
};

//Преобразование даты из строки вида day.month.year в тип дата
Date DateFromString(string str);