#include "Computer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace NameComp
{
	ostream& manipStr(ostream& out)
	{
		return out
			<< setw(15)
			<< setfill('.')
			<< resetiosflags(ios::right)
			<< setiosflags(ios::left);
	}

	ostream& manipInt(ostream& out)
	{
		return out
			<< setw(8)
			<< setfill('.')
			<< resetiosflags(ios::left)
			<< setiosflags(ios::right);
	}

	ostream& operator<<(ostream& out, const COMP& comp)
	{
		return out
			<< manipStr << comp.name
			<< manipInt << comp.memory
			<< manipInt << comp.frequency;
	}

	istream& operator>>(istream& in, COMP& comp)
	{
		getline(in, comp.name, ';');

		string tmp;
		getline(in, tmp, ';');
		comp.frequency = atoi(tmp.c_str());

		getline(in, tmp, '\n');
		comp.memory = atoi(tmp.c_str());

		return in;
	}

	void input(COMP* array, size_t n, istream& in)
	{
		size_t i = 0;
		while (i < n && !in.eof())
			in >> array[i++];
	}

	void output(const COMP* array, size_t n, ostream& out)
	{
		for (size_t i = 0; i < n; i++)
			out << array[i] << endl;
	}

	void sort_computers(COMP array[], size_t n)
	{
		for (size_t i = 0; i < n - 1; i++)
		{
			for (size_t j = i + 1; j < n; j++)
			{
				if (array[i].name > array[j].name)
				{
					COMP tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
				}
			}
		}

	}

	const COMP* find_comp(const COMP* array, size_t n)
	{
		string query;
		cout << "Query: ";
		getline(cin, query);

		const COMP* result = NULL;

		for (size_t i = 0; i < n; i++)
		{
			if (array[i].name.find(query) != string::npos)
			{
				result = &array[i];
				break;
			}
		}

		return result;
	}

	void freq_above_average(const COMP array[], size_t n, ostream& out)
	{
		double average = 0;
		for (size_t i = 0; i < n; i++)
			average += array[i].frequency;
		average /= n;

		out << "TASK 3. Computers whose CPU frequency is higher than average" << endl;
		out << "Average CPU freq: " << average << endl << endl;
		for (size_t i = 0; i < n; i++)
		{
			if (array[i].frequency >= average)
				out << array[i] << endl;
		}
		out << endl;
	}
}