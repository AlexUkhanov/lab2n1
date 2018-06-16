/*
Задача 2 №1
Результатом должна быть консольная программа с текстовым меню. 
Программа должна содержать шаблонный класс для управления данными согласно заданию. Для хранения данных 
необходимо выбрать оптимальный с точки зрения задания контейнер.
	1)Предусмотреть операции добавления, изменения и удаления элемента контейнера.
	2)Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл.
	3)Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным критериям. 
	Реализовать поиск в двух вариантах: линейный поиск и двоичный поиск на отсортированном контейнере.
	4)Предусмотреть вывод подмножества выборки на экран и в файл.

Счет в банке представляет собой структуру с полями: номер счета, код счета, 
фамилия владельца, сумма на счете, дата открытия счета, годовой процент начисления. 
Поиск по номеру счета, дате открытия и владельцу.

*/
#include <string>
#include "Account.h"
#include "Task.h"

int Menu()
{
	cout << " ------------------------------------Menu---------------------------------------  " << endl;
	cout << "1 - Add element" << endl;
	cout << "2 - Delete element" << endl;
	cout << "3 - Change element" << endl;
	cout << "4 - Print to the screen" << endl;
	cout << "5 - Save to file " << endl;
	cout << "6 - Linear search" << endl;
	cout << "7 - Binary search" << endl;
	cout << "8 - Display the subset on the screen" << endl;
	cout << "9 - Save a subset to a file" << endl;
	cout << "0 - Exit" << endl;
	int n = InputNumber(0, 9, "Your choise: ");
	cout << "\n";
	return n;
}

int main()
{
	Task<Account> accs;
	bool change = false;
	int changemenu=-1;
	while ((!change)&&changemenu)
	{
		cout << " ------------------------------------Menu---------------------------------------  " << endl;
		cout << "1 - Filling the container from the console" << endl;
		cout << "2 - Filling the Container from a File " << endl;
		cout << "0 - Exit" << endl;
		changemenu = InputNumber(0, 2, "Your choise: ");
		switch (changemenu)
		{
		case 1:
			change=true;
			accs.ReadFromScreen(InputAccount);
			break;

		case 2:
			change = accs.ReadFromFile(ReadFromString);
			break;

		default:
			change = false;
			break;
		}
	}
	if (change)
	{
		Account elem;
		vector<Account> subset;
		Account search_elem;
		int number;
		int n = Menu();
		while (n)
		{
			switch (n)
			{
			case 1:
				accs.Add(InputAccount());
				break;

			case 2:
				accs.OutputScreen(accs.vect, PrintConsole);
				accs.Remove(InputNumber(0, accs.size(), "Enter the number of the element to remove (0 - to cancel) : "));
				break;

			case 3:
				accs.OutputScreen(accs.vect, PrintConsole);
				number = InputNumber(0, accs.size(), "Enter the number of the element to change (0 - to cancel) : ");
				if (number != 0)
					accs.vect[number - 1] = elem.ChangeAccount(accs.vect[number - 1]);
				break;

			case 4:
				accs.OutputScreen(accs.vect, PrintConsole);
				break;

			case 5:
				accs.OutputFile(accs.vect, ToString_);
				break;

			case 6:
				number = InputNumber(1, 3, "Choise type of search:\n 1 - by account number\n 2 - by date\n 3 - by surname \nYour choise: ");
				search_elem = InputChangeTypeSearch(number);
				subset = accs.LinearySearch(search_elem, SearchElement, number);
				if (subset.size() != 0)
					accs.OutputScreen(subset, PrintConsole);
				else
					cout << "Elements is not found" << endl;
				break;

			case 7:
				number = InputNumber(1, 3, "Choise type of search:\n 1 - by account number\n 2 - by date\n 3 - by surname \nYour choise: ");
				search_elem = InputChangeTypeSearch(number);
				subset = accs.BinarySearch(number, search_elem, Sort, SearchElement);
				if (subset.size() != 0)
					accs.OutputScreen(subset, PrintConsole);
				else
					cout << "Elements is not found" << endl;
				break;

			case 8:
				accs.OutputScreen(subset, PrintConsole);
				break;

			case 9:
				accs.OutputFile(subset, ToString_);
				break;
			}
			n = Menu();
		}
	}
    return 0;
}

