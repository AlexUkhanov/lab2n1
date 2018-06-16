#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <ostream>
using namespace std;

//Функция для ввода числа в заданном диапазоне с сообщением message
template <class Type>
Type InputNumber(Type min, Type max, string message)
{	
	while (true)
	{
		cout << message << endl;
		Type res;
		cin >> res;
		if (cin.fail()) // если предыдущее извлечение оказалось провальным
		{
			cin.clear(); // возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
		if ((res < min) || (res > max))
			cout << "Incorrect number entered. Re-enter please" << endl;
		else
			return res;
	}
};
//Функция для ввода строковой информации
string InputInformation(string message);
//Проверка символа на корректность в имени файла
bool CorrectSymbol(char c);
//проверка имени файла на коректность
bool CorrectName(string name);
//Ввод имени файла
string InputFileName();
//Обрезка строки
string trim(const string& str);