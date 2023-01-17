#pragma once
#include <vector>

template <typename T>
class Library_Base
{
protected:
	size_t n_books;
	std::vector<T> books;

public:
	Library_Base() : n_books(1), books(1, T()) {}
	Library_Base(size_t num) : n_books(num), books(num, T()) {}
	Library_Base(const Library_Base& lib)
	{
		if (this == &lib)
			return;

		this->n_books = lib.n_books;

		books = lib.books;
	}

	virtual ~Library_Base() {}

	virtual void input() = 0;
	virtual void output() = 0;
};

