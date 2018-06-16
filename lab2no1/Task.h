#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Account.h"
#include "HelpUtils.h"
using namespace std;


template <class Type>
class Task
{
private:
	// бинарный поиск
	// int(*Compare)(Type, Type, int) - указатель на функцию, которая сравнивает искомый эл-т с текущим по type_search  
	int Binary_Search_Element(int left, int right, int type_search, Type d, int(*Compare)(Type, Type, int))
	{
		int middle = 0;
		while (1)
		{
			middle = (left + right) / 2;

			if (Compare(d, vect[middle], type_search) == -1)// если искомое больше значения в ячейке
				right = middle - 1;				// смещаем правую границу поиска
			else if (Compare(d, vect[middle], type_search) == 1)  // если искомое меньше значения в ячейке
				left = middle + 1;					// смещаем левую границу поиска
			else                       // иначе (значения равны)
				return middle;           // функция возвращает индекс ячейки

			if (left > right)          // если границы сомкнулись 
				return -1;
		}
	}
	// сортировка по заданному критерию
	// int(*Compare)(Type, Type, int) - указатель на функцию, которая сравнивает искомый эл-т с текущим по type_search  
	void ShellSort(int n, int typ, int(*Compare)(Type, Type, int))
	{
		int i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], typ) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}
public:
	vector<Type> vect;
	Task() {}
	~Task() {}

	// удаление элемента
	void Remove(int numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb - 1);
	}

	// добавление элемента
	void Add(Type &elem)
	{
		vect.push_back(elem);
	}

	//размер вектора
	int size()
	{
		return vect.size();
	}

	// проверка на пустоту
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	// вывод в файл
	// void(*f) (Type) - указатель на функцию, которая записывает одну структуру в файл  
	void OutputFile(vector<Type> items, string(*f)(Type, int))
	{
		string FileName = InputFileName();
		ofstream fout(FileName);
		if (fout)
		{
			vector<Type>::const_iterator pos;
			int count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count);
				count++;
			}
			fout.close();
		}
		else
		{
			cout << "Error of filling file!" << endl;
		}
	}

	// вывод на экран
	// void(*f) (Type) - указатель на функцию, которая записывает одну структуру на экран  
	void OutputScreen(vector<Type> items, void(*f) (Type))
	{
		vector<Type>::const_iterator pos;
		if (items.begin() == items.end())
			cout << "Sequence is empty!" << endl;
		else
		{
			cout << "---------------------------------------------------------------------------------\n";
			cout << setw(10) << setiosflags(ios::left) << "| Number" << '|';
			cout << setw(10) << setiosflags(ios::left) << "Code" << '|';
			cout << setw(15) << setiosflags(ios::left) << "Surname" << '|';
			cout << setw(15) << setiosflags(ios::left) << "Amount" << '|';
			cout << setw(15) << setiosflags(ios::left) << "Data" << '|';
			cout << setw(10) << setiosflags(ios::left) << "Percent" << '|' << endl;
			cout << "---------------------------------------------------------------------------------\n";
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				f(*pos);
			}
		}
	}

	// ввод из файла
	// Type(*f)(ifstream&) - указатель на функцию, которая считывает одну структуру из файла 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		std::ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "Could not open file." << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	// ввод с экрана
	//Type(*f)() - указатель на функцию, которая вводит одну структуру с консоли
	void ReadFromScreen(Type(*f)())
	{
		int n;
		Type elem;
		do
		{
			vect.push_back(f());
			n = InputNumber<int>(0, 1, "Do you want to add the element? (1 - yes, 0 - no)\nYour choise: ");
		} while (n != 0);
	}

	// линейный поиск
	// bool(*Equal)(Type, Type, int) - указатель на функцию, которая проверяет равенство искомого эл-та с текущим по type_search
	vector<Type> LinearySearch(Type search_elem, bool(*Equal)(Type, Type, int), int type_search)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem, *iter, type_search))
				NewVect.push_back(*iter);
		}
		return NewVect;
	}

	// бинарный поиск
	// int(*Compare)(Type, Type, int) - указатель на функцию, которая сравнивает искомый эл-т с текущим по type_search 
	// bool(*Equal)(Type, Type, int) - указатель на функцию, которая проверяет равенство искомого эл-та с текущим по type_search
	vector<Type> BinarySearch(int type_search, Type find_element, int(*Compare)(Type, Type, int), bool(*Equal)(Type, Type, int))
	{
		vector<Type> NewVect;
		ShellSort(vect.size(), type_search, Compare);
		int left = 0;
		int right = vect.size();
		int index;
		if ((index = Binary_Search_Element(left, right - 1, type_search, find_element, Compare)) != -1)
		{
			NewVect.push_back(vect[index]);
			int first_index = index;
			while ((++index<right) && Equal(vect[index], find_element, type_search))
				NewVect.push_back(vect[index]);
			while ((--first_index >= 0) && Equal(vect[first_index], find_element, type_search))
				NewVect.push_back(vect[first_index]);
		}
		return NewVect;
	}
};