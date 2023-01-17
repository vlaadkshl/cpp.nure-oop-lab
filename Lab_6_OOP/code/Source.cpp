#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include "funcs.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	ofstream f_out("output.txt");

	map<string, multiset<size_t>> result;	//	јсоц≥ативний контейнер результат≥в
	set<string> excepts;					//	ћножина сл≥в-вин€тк≥в

	/*
		«читуванн€ сл≥в-вин€тк≥в
	*/
	ifstream f_excepts("excepts.txt");
	while (!f_excepts.eof())
	{
		string tmp;
		getline(f_excepts, tmp, ',');
		excepts.emplace(tmp);
	}
	f_excepts.close();

	/*
		«читуванн€ тексту
	*/
	ifstream f_text("input.txt");
	string tmp;
	for (size_t i = 1; !f_text.eof(); i++)
	{
		getline(f_text, tmp, '\n');
		istringstream tmp_stream(tmp);
		while (!tmp_stream.eof())
		{
			string tmp_string;
			getline(tmp_stream, tmp_string, ' ');

			//	якщо знайдене слово не належить до множини вин€тк≥в,
			//	то додаЇмо до масиву пару <слово, р€док>
			if (excepts.find(tmp_string) == excepts.end())
				result[tmp_string].emplace(i);
			//	 ожен раз, коли зустр≥лос€ слово з≥ списку, виводити пов≥домленн€
			else
				Out::is_in_exception_list(f_out, tmp_string, i);
		}
	}

	map<string, set<size_t>> how_many_double;
	for (auto elem : result)
	{
		for (size_t i : elem.second)
		{
			size_t count_double = count(elem.second.begin(), elem.second.end(), i);

			if (count_double == 2)
				how_many_double[elem.first].emplace(i);
		}
	}

	//	якщо слово зустр≥лос€ в одному р€дку дв≥ч≥ - виводити пов≥домленн€
	cout << "\nƒва раза:\n";
	f_out << "\nƒва раза:\n";
	for (auto elem : how_many_double)
		Out::is_double(f_out, elem.first, elem.second);

	return 0;
}