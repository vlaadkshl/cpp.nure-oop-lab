#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

namespace Out
{
	void is_in_exception_list(ofstream& file, string str, size_t line);
	void is_double(ofstream& file, string word, set<size_t> lines);
}