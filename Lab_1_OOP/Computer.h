#pragma once
#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <string>

using namespace std;

namespace NameComp
{
	struct COMP
	{
		string name;
		size_t frequency, memory;
	};

	ostream& manipStr(ostream& out);
	ostream& manipInt(ostream& out);

	ostream& operator<<(ostream& out, const COMP& comp);
	istream& operator>>(istream& in, COMP& comp);

	void input(COMP* group, size_t n, istream& in);
	void output(const COMP* group, size_t n, ostream& out);

	void sort_computers(COMP array[], size_t n);
	const COMP* find_comp(const COMP* array, size_t n);
	void freq_above_average(const COMP array[], size_t n, ostream& out);
}

#endif