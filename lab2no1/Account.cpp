#include "Account.h"

//Конструктор
Account::Account()
{
	no = 0;
	code = 0;
	surname = "";
	amount = 0;
	percent=0;
}
//Изменение записи счета
Account Account::ChangeAccount(Account &result)
{
	if (InputNumber(0, 1, "Do you want to change number of account " + to_string(result.no) + "? (0 - no, 1 - yes)\nYour choise: ") == 1)
		result.no = InputNumber(0,999999,"Input new number of account: ");
	if (InputNumber(0, 1, "Do you want to change code of account " + to_string(result.code) + "? (0 - no, 1 - yes)\nYour choise: ") == 1)
		result.code = InputNumber(0,999,"Input new code of account:");
	if (InputNumber(0, 1, "Do you want to change surname " + result.surname + "? (0 - no, 1 - yes)\nYour choise: ") == 1)
		result.surname = InputInformation("Input new surname: ");
	if (InputNumber(0, 1, "Do you want to change amount of money on the account " + to_string(result.amount) + "? (0 - no, 1 - yes)\nYour choise: ") == 1)
		result.amount = InputNumber(0, 1000000, "Input new amount of money (0 - 1000000): ");
	if (InputNumber(0, 1, "Do you want to change date of open "+result.date_open.ToString()+"? (0 - no, 1 - yes) \nYour choise: ") == 1)
		result.date_open.InputDate();
	if (InputNumber(0, 1, "Do you want to change percent " + to_string(result.percent) + "? (0 - no, 1 - yes)\nYour choise: ") == 1)
		result.percent = InputNumber(0,100,"Input new percent");
	return result;
}
//Преобразование в строку
string Account::ToString()
{
	string res = "No: " + to_string(no) + "\nCode: " + to_string(code) + "\nSurname: " + surname + "\nAmount: " + to_string(amount) + "\nDate: " + date_open.ToString() + "\nPercent: " + to_string(percent) + "\n";
	return res;
}
//Перегруженный оператор присваивания
Account& Account::operator = (Account ac)
{
	no = ac.no;
	code = ac.code;
	surname = ac.surname;
	date_open = ac.date_open;
	amount = ac.amount;
	percent = ac.percent;
	
	return (*this);
}

//Ввод данных о счете с консоли
Account InputAccount()
{
	Account res;
	res.no = InputNumber(100000, 999999, "Input number of account (100000-999999): ");
	res.code = InputNumber(100, 999, "Input code of account (100-999):");
	res.surname = InputInformation("Input surname: ");
	res.amount = InputNumber<double>(0, 1000000, "Input amount of money (0 - 1000000): ");
	res.date_open.InputDate();
	res.percent = InputNumber<double>(0, 100, "Input percent (0-100)");

	return res;
}

//Вывод данных о счете на консоль
void PrintConsole(Account a)
{
	cout<<setw(1)<<setiosflags(ios::left)<<'|'<< setw(9) << setiosflags(ios::left) << to_string(a.no) << '|';
	cout<<setw(10)<<setiosflags(ios::left)<<to_string(a.code)<<'|';
	cout<<setw(15)<<setiosflags(ios::left)<<a.surname<<'|';
	cout<<setw(15)<<setiosflags(ios::left)<< setprecision(4) <<a.amount<<'|';
	cout<<setw(15)<<setiosflags(ios::left)<<a.date_open.ToString()<<'|';
	cout<<setw(10)<< setiosflags(ios::left)<<setprecision(4)<< a.percent << '|' << endl;
	cout << "---------------------------------------------------------------------------------\n";
}

//считывание данных счета из строки
Account ReadFromString(ifstream& input)
{
	Account result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "No: ";
			result.no = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Code: ";
			result.code = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Surname: ";
			result.surname = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Amount: ";
			result.amount = atof(s.substr(wrd.length(), s.length()).c_str());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Date: ";
			result.date_open = DateFromString(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Percent: ";
			result.percent = atof(s.substr(wrd.length(), s.length()).c_str());
		}
	}
	catch (...)
	{
		cout << "Error of reading!" << endl;
	}
	return result;
}

//Перевод в строку данных счета
string ToString_(Account ac)
{
	return ac.ToString();
}

//Перевод в строку данных счета + вывод номера записи
string ToString_(Account ac,int i)
{
	return "Record No."+to_string(i)+"\n"+ac.ToString();
}

// поиск равного элемента по выбранному критерию
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
bool SearchElement(Account m, Account n, int type_search)
{
	string upper_m = trim(m.surname);
	string upper_n = trim(n.surname);
	switch (type_search)
	{
	case 1:
		return (m.no == n.no);
	case 2:
		return (m.date_open == n.date_open);
	case 3:
		for (auto i = upper_m.begin(); i != upper_m.end(); i++)
		{
			*i = toupper(*i);
		}
		for (auto i = upper_n.begin(); i != upper_n.end(); i++)
		{
			*i = toupper(*i);
		}
		return (!(upper_m.compare(upper_n)));
	default:
		return false;
	}
}

// ввод критерия поиска в зависимости от выбранного типа 
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
Account InputChangeTypeSearch(int type_search)
{
	Account result;
	switch (type_search)
	{
	case 1:
		result.no = InputNumber(0, 999999, "Input number of account: ");
		return result;
	case 2:
		result.date_open.InputDate();
		return result;
	case 3:
		result.surname = InputInformation("Input surname: ");
		return result;
	default:
		return result;
	}
}

// сравнение счетов в зависимости от выбранного поля для сортировки
// type_search - тип поиска
//1 - по номеру счета
//2 - по дате открытия
//3 - по фамилии
int Sort(Account n, Account m, int type_search)
{
	string upper_m = trim(m.surname);
	string upper_n = trim(n.surname);
	switch (type_search)
	{
	case 1:
		if (n.no > m.no) return 1;
		else if (n.no < m.no) return -1;
		else return 0;
	case 2:
		if (n.date_open > m.date_open) return 1;
		else if (n.date_open < m.date_open) return -1;
		else return 0;
	case 3:
		for (auto i = upper_m.begin(); i != upper_m.end(); i++)
		{
			*i = toupper(*i);
		}
		for (auto i = upper_n.begin(); i != upper_n.end(); i++)
		{
			*i = toupper(*i);
		}
		if (upper_n > upper_m) return 1;
		else if (upper_n < upper_m) return -1;
		else return 0;
	default:
		return -2;
	}
}