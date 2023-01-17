#include <iostream>
#include <string>
#include <vector>
#include "Library_Base.h"

using namespace std;

struct Specialization
{
	string city, street;
	size_t number;

	Specialization() : city("New York"), street("Example str."), number(1) {}

	Specialization(string city, string street, size_t number) : city(city), street(street), number(number) { }

	Specialization(const Specialization& copy)
	{
		this->city = copy.city;
		this->street = copy.street;
		this->number = copy.number;
	}

	bool operator==(const Specialization& spec)
	{
		Specialization first = *this;

		if (first.city == spec.city
			&& first.number == spec.number
			&& first.street == spec.street)
			return true;
		else return false;
	}

	ostream& print(ostream& out) const
	{
		out << city << ", " << street << " str., " << number;
		return out;
	}

	operator double() { return (double)number; }
};
ostream& operator<<(ostream& out, Specialization& spec)
{
	out << spec.city << ", " << spec.city << " str., " << spec.number;
	return out;
}
istream& operator>>(istream& in, Specialization spec)
{
	string tmpstr;
	size_t tmpint;

	cout << "City: ";
	in >> tmpstr;
	spec.city = tmpstr;

	cout << "Street: ";
	tmpstr = "";
	in >> tmpstr;
	spec.street = tmpstr;

	cout << "Number: ";
	tmpstr = "";
	in >> tmpint;
	spec.number = tmpint;

	return in;
}

struct Book
{
	string name;
	size_t year, amount_available, amount_checkedout;

	Book() : name("Example"), year(2000), amount_available(1), amount_checkedout(5) {}

	Book(string name, size_t year, size_t amount_available, size_t amount_checkedout) :
		name(name), year(year), amount_available(amount_available), amount_checkedout(amount_checkedout) { }

	Book(const Book& book)
	{
		this->name = book.name;
		this->year = book.year;
		this->amount_available = book.amount_available;
		this->amount_checkedout = book.amount_checkedout;
	}

	Book operator=(const Book& book)
	{
		this->name = book.name;
		this->year = book.year;
		this->amount_available = book.amount_available;
		this->amount_checkedout = book.amount_checkedout;

		return *this;
	}

	Book operator++()
	{
		this->amount_available++;
		return *this;
	}

	operator double() { return (double)this->year; }
};
ostream& operator<<(ostream& out, Book& book)
{
	out << "Name: " << book.name << "\t Year: " << book.year << "\n Available: " << book.amount_available << "\t Published: " << book.amount_checkedout;
	return out;
}
istream& operator>>(istream& in, Book& book)
{
	cout << "Add new book" << endl;

	string tmpstr = "";
	getline(in, tmpstr);
	int tmpint;

	cout << "Name: ";
	getline(in, tmpstr);
	book.name = tmpstr;

	cout << "Year: ";
	while (true)
	{
		tmpstr = "";
		getline(in, tmpstr);
		tmpint = atoi(tmpstr.c_str());

		if (tmpint < 0 || tmpint > 2022)
		{
			cout << "Try another one..." << endl;
			continue;
		}
		else
		{
			book.year = tmpint;
			break;
		}
	}

	cout << "Available: ";
	while (true)
	{
		tmpstr = "";
		getline(in, tmpstr);
		tmpint = atoi(tmpstr.c_str());

		if (tmpint < 0)
		{
			cout << "Try another one..." << endl;
			continue;
		}
		else
		{
			book.amount_available = tmpint;
			break;
		}
	}

	cout << "Published: ";
	while (true)
	{
		tmpstr = "";
		getline(in, tmpstr);
		tmpint = atoi(tmpstr.c_str());

		if (tmpint > book.amount_available || tmpint < 0)
		{
			cout << "Try another one..." << endl;
			continue;
		}
		else
		{
			book.amount_checkedout = tmpint;
			break;
		}
	}

	return in;
}

class Library : public Library_Base<Book>
{
	string name;

public:
	Specialization specialization;

	Library() : Library_Base<Book>(), name("Library"), specialization() {}

	Library(string name, Specialization spec, vector<Book> books)
	{
		this->name = name;
		specialization = spec;
		this->books = books;
	}

	Library(string name, Specialization spec, size_t n_books) : Library_Base(n_books)
	{
		this->name = name;
		specialization = spec;
	}

	Library(const Library& lib)
	{
		name = lib.name;
		specialization = lib.specialization;
		books = lib.books;
	}

	Library& operator=(const Library& lib)
	{
		name = lib.name;
		specialization = lib.specialization;
		books = lib.books;

		return *this;
	}

	string getName() const { return name; }
	void setName(string name) { this->name = name; }

	vector<Book> getBooks() const { return books; }

	virtual void input()
	{
		cout << "Input " << n_books << " books...\n";
		for (size_t i = 0; i < n_books; i++)
		{
			cout << i + 1 << " BOOK:\n";
			Book tmp;
			cin >> tmp;
			books.push_back(tmp);
		}
	}

	virtual void output()
	{
		for (size_t i = 0; i < n_books; i++)
			cout << books[i];
	}

	void getNameAndAdress(ostream& out)
	{
		out << "FIRST TASK:" << endl;
		out << "Name: " << name << "\tAdress: " << specialization << endl << endl;
	}

	void isBookAvailable(ostream& out) const
	{
		out << "SECOND TASK:" << endl;

		string tmp;
		cout << "Enter book name: ";
		cin >> tmp;

		for (size_t i = 0; i < n_books; i++)
		{
			if (tmp == books[i].name)
				out << "Book " << tmp << " is available" << endl << endl;
			else
				out << "Book " << tmp << " isn't available" << endl << endl;
		}
	}

	void averageCheckedout(ostream& out) const
	{
		out << "THIRD TASK" << endl;

		double average = 0;
		for (size_t i = 0; i < books.size(); i++)
			average += books[i].amount_checkedout;
		average /= books.size();

		out << "The average number of checked out books is " << average << endl << endl;
	}

	void addBook(ostream& out)
	{
		out << "FOURTH TASK:" << endl;

		Book tmp;
		cin >> tmp;

		books.push_back(tmp);
		out << tmp.name << " (" << tmp.year << ") is added" << endl << endl;
	}

	void removeBook(ostream& out)
	{
		out << "FIFTH TASK:" << endl;

		cout << "Book list:" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << i + 1 << ".\t";
			cout << books[i].name << "\t";
			cout << books[i].year << endl;
		}

		bool isCorrect = false;
		cout << "What book do you want to remove?\nEnter number: ";
		string tmp;
		size_t tmpint;
		while (!isCorrect)
		{
			cin >> tmp;
			tmpint = atoi(tmp.c_str());

			if (tmpint > books.size() || tmpint < 1)
				continue;
			else
				isCorrect = true, tmp = "";
		}

		for (size_t i = 0; i < books.size(); i++)
		{
			if (tmpint == (i + 1))
			{
				books.erase(books.begin() + i);
				out << "Completed." << endl;
				break;
			}
		}

		out << "New book list is:" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			out << i + 1 << ".\t";
			out << books[i].name << "\t";
			out << books[i].year << endl;
		}

		out << endl;
	}

	void giveBook(ostream& out)
	{
		out << "SIXTH TASK:" << endl;

		cout << "Book list" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << i + 1 << ".\t";
			cout << books[i].name << "\t";
			cout << books[i].year << endl;
		}

		bool isCorrect = false;
		cout << "What book do you want to check out?\nEnter number: ";
		string tmp;
		size_t tmpint;
		while (!isCorrect)
		{
			cin >> tmp;
			tmpint = atoi(tmp.c_str());

			if (tmpint > books.size() || tmpint < 1)
				continue;
			else
				isCorrect = true, tmp = "";
		}
		tmpint--;

		if (books[tmpint].amount_checkedout < books[tmpint].amount_available)
		{
			books[tmpint].amount_checkedout++;
			out << "Book " << books[tmpint].name << " is checked out" << endl << endl;
		}
		else out << "All books are checked out earlier." << endl << endl;
	}

	void howManyBooksGiven(ostream& out) const
	{
		out << "SEVENTH TASK:" << endl;

		double percentage = 0;
		for (size_t i = 0; i < books.size(); i++)
			if (books[i].amount_checkedout == books[i].amount_available)
				percentage++;
		percentage /= (books.size());
		percentage *= 100;

		out << "Percentage of fully given book is " << percentage << "%" << endl;
	}

	~Library() {}
};
ostream& operator<<(ostream& out, Library& lib)
{
	out << "LIBRARY:\n";
	out << "Name: " << lib.getName() << "\nSpecialization:\n" << lib.specialization << "\nBooks:\n";
	for (size_t i = 0; i < lib.getBooks().size(); i++)
		out << lib.getBooks()[i] << endl;

	return out;
}

int main()
{
	Library lib("Name", Specialization("City", "Street", 5), 2);

	//	«ј¬ƒјЌЌя 1:
	//	ƒ≥знатис€ назву та адресу б≥бл≥отеки
	lib.getNameAndAdress(cout);

	//	«ј¬ƒјЌЌя 2:
	//	ѕерев≥рити на€вн≥сть книги за назвою
	lib.isBookAvailable(cout);

	//	«ј¬ƒјЌЌя 3:
	//	ƒ≥знатис€ середнЇ число виданих книг
	lib.averageCheckedout(cout);

	//	«ј¬ƒјЌЌя 4:
	//	ƒодати книгу до б≥бл≥отеки
	lib.addBook(cout);

	//	«ј¬ƒјЌЌя 5:
	//	¬идалити книгу з б≥бл≥отеки
	lib.removeBook(cout);

	//	«ј¬ƒјЌЌя 6:
	//	¬идати книгу на руки (зб≥льшити к≥льк≥сть виданих книг)
	lib.giveBook(cout);

	//	«ј¬ƒјЌЌя 7:
	//	ѕ≥драхувати процент книжок, €к≥ повн≥стю видан≥
	lib.howManyBooksGiven(cout);

	system("pause");
	return 0;
}