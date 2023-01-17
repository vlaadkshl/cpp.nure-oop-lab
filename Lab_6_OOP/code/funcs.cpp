#include "funcs.h"

void Out::is_in_exception_list(ofstream& file, string str, size_t line)
{
	cout << "\"" << str << "\" ��������� � ������ ����������. � ������ � �� " << line << " ������.\n";
	file << "\"" << str << "\" ��������� � ������ ����������. � ������ � �� " << line << " ������.\n";
}

void Out::is_double(ofstream& file, string word, set<size_t> lines)
{
	cout << word << " � ";
	for (size_t i : lines)
		cout << i << "\t";
	cout << "\n";

	file << word << " � ";
	for (size_t i : lines)
		file << i << "\t";
	file << "\n";
}