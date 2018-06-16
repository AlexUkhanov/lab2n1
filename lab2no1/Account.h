#pragma once
#include <string>
#include "DateUtils.h"
#include "HelpUtils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class Account
{
public:
	//Номер счета
	int no;
	//Код
	int code;
	//Фамилия
	string surname;
	//Сумма на счету
	double amount;
	//Дата открытия
	Date date_open;
	//Процент начисления
	double percent;
	//Конструктор
	Account();
	//Изменение записи счета
	Account ChangeAccount(Account &result);
	//Преобразование в строку
	string ToString();
	//Перегруженный оператор присваивания
	Account& operator = (Account ac);
};


//Ввод данных о счете с консоли
Account InputAccount();

//считывание данных счета из строки
Account ReadFromString(ifstream& input);

//Вывод данных о счете на консоль
void PrintConsole(Account ac);

// поиск равного элемента по выбранному критерию
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
bool SearchElement(Account m, Account n, int type_search);
// ввод критерия поиска в зависимости от выбранного типа 
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
Account InputChangeTypeSearch(int type_search);
// сравнение счетов в зависимости от выбранного поля для сортировки
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
int Sort(Account n, Account m, int type_search);
//Перевод в строку данных счета
string ToString_(Account ac);
//Перевод в строку данных счета + вывод номера записи
string ToString_(Account ac, int i);