#include "HelpUtils.h"
#include <iostream>

//Функция для ввода строковой информации
string InputInformation(string message)
{
	string a;
	cout << message << endl;
	cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
	getline(cin,a);
	while (trim(a) == "")
	{
		cout << "Error.Re-enter please:" << endl;
		getline(cin,a);
	}
	return a;
}

// проверка символа на корректность в имени файла
bool CorrectSymbol(char c)
{
	switch (c)
	{
	case '.':
	case '*':
	case '?':
	case '<':
	case '>':
	case ':':
	case '|':
	case '/':
		return false;
	default:
		return true;
	}
}


// проверка имени файла на коректность
bool CorrectName(string name)
{
	int i = 0;
	bool goodsm = true;
	for (int i = 0; (i < name.length() && goodsm); i++)
		goodsm = CorrectSymbol(name[i]);
	return goodsm;
}

// ввод имени файла
string InputFileName()
{

	string filename;
	do
	{
		cout << "Enter filename:  ";
		cin >> filename;
		if (filename.length() > 35)
			filename.erase(filename.begin(), filename.begin() + 35);
		if (CorrectName(filename))
		{
			filename = filename + ".txt";
			break;
		}
		else
			cout << "Incorrect filename\n";
	} while (true);

	return filename;
}

//Обрезка строки
string trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}