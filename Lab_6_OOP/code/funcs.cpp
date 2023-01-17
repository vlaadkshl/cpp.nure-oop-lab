#include "funcs.h"

void Out::is_in_exception_list(ofstream& file, string str, size_t line)
{
	cout << "\"" << str << "\" находится в списке исключений. В тексте – на " << line << " строке.\n";
	file << "\"" << str << "\" находится в списке исключений. В тексте – на " << line << " строке.\n";
}

void Out::is_double(ofstream& file, string word, set<size_t> lines)
{
	cout << word << " в ";
	for (size_t i : lines)
		cout << i << "\t";
	cout << "\n";

	file << word << " в ";
	for (size_t i : lines)
		file << i << "\t";
	file << "\n";
}