#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Specialization
{
	string city, street;
	size_t number;
public:
	Specialization() : city("New York"), street("Example str."), number(1) {}

	Specialization(string city, string street, size_t number)
	{
		this->city = city;
		this->street = street;
		this->number = number;
	}

	Specialization(const Specialization& copy)
	{
		this->city = copy.city;
		this->street = copy.street;
		this->number = copy.number;
	}

	Specialization& operator=(const Specialization& copy)
	{
		this->city = copy.city;
		this->street = copy.street;
		this->number = copy.number;

		return *this;
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

	string getCity() const { return city; }
	string getStreet() const  { return street; }
	size_t getNumber() const { return number; }

	void setCity(string city) { this->city = city; }
	void setStreet(string street) { this->street = street; }
	void setNumber(size_t number) { this->number = number; }

	~Specialization() {}
};
ostream& operator<<(ostream& out, Specialization& spec)
{
	out << spec.getCity() << ", " << spec.getStreet() << " str., " << spec.getNumber();
	return out;
}
istream& operator>>(istream& in, Specialization spec)
{
	string tmpstr;
	size_t tmpint;

	cout << "City: ";
	in >> tmpstr;
	spec.setCity(tmpstr);

	cout << "Street: ";
	tmpstr = "";
	in >> tmpstr;
	spec.setStreet(tmpstr);

	cout << "Number: ";
	tmpstr = "";
	in >> tmpint;
	spec.setNumber(tmpint);

	return in;
}

class Book
{
	string name;
	size_t year, amount_available, amount_checkedout;
public:
	Book() : name("Example Book"), year(2000), amount_available(1), amount_checkedout(5) {}

	Book(string name, size_t year, size_t amount_available, size_t amount_checkedout)
	{
		this->name = name;
		this->year = year;
		this->amount_available = amount_available;
		this->amount_checkedout = amount_checkedout;
	}

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

	bool operator!=(const Book& book)
	{
		if (this->amount_available != book.amount_available)
			return true;
		else return false;
	}

	operator double() { return (double)this->year; }

	string getName() const { return name; }
	size_t getYear() const { return year; }
	size_t getAmountAvailable() const { return amount_available; }
	size_t getAmountCheckedout() const { return amount_checkedout; }

	void setName(string name) { this->name = name; }
	void setYear(size_t year) { this->year = year; }
	void setAmountAvailable(size_t amount) { amount_available = amount; }
	void setAmountCheckedout(size_t amount) { amount_checkedout = amount; }

	~Book() {}
};
ostream& operator<<(ostream& out, Book& book)
{
	out << "Name: " << book.getName() << "\t Year: " << book.getYear() << "\n Available: " << book.getAmountAvailable() << "\t Published: " << book.getAmountCheckedout();
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
	book.setName(tmpstr);

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
			book.setYear(tmpint);
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
			book.setAmountAvailable(tmpint);
			break;
		}
	}

	cout << "Published: ";
	while (true)
	{
		tmpstr = "";
		getline(in, tmpstr);
		tmpint = atoi(tmpstr.c_str());

		if (tmpint > book.getAmountAvailable() || tmpint < 0)
		{
			cout << "Try another one..." << endl;
			continue;
		}
		else
		{
			book.setAmountCheckedout(tmpint);
			break;
		}
	}

	return in;
}

class Library
{
	string name;

public:
	Specialization specialization;
	vector<Book> books;

	Library() : name("Library"), specialization() { books.push_back({}); }

	Library(string name, Specialization spec, vector<Book> books)
	{
		this->name = name;
		specialization = spec;
		this->books = books;
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

	Library operator++() { books.push_back(Book()); }

	string getName() const { return name; }
	void setName(string name) { this->name = name; }

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

		for (size_t i = 0; i < books.size(); i++)
		{
			if (tmp == books[i].getName())
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
			average += books[i].getAmountCheckedout();
		average /= books.size();

		out << "The average number of checked out books is " << average << endl << endl;
	}

	void addBook(ostream& out)
	{
		out << "FOURTH TASK:" << endl;

		Book tmp;
		cin >> tmp;

		books.push_back(tmp);
		out << tmp.getName() << " (" << tmp.getYear() << ") is added" << endl << endl;
	}

	void removeBook(ostream& out)
	{
		out << "FIFTH TASK:" << endl;

		cout << "Book list:" << endl;
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << i + 1 << ".\t";
			cout << books[i].getName() << "\t";
			cout << books[i].getYear() << endl;
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
			out << books[i].getName() << "\t";
			out << books[i].getYear() << endl;
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
			cout << books[i].getName() << "\t";
			cout << books[i].getYear() << endl;
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

		if (books[tmpint].getAmountCheckedout() < books[tmpint].getAmountAvailable())
		{
			books[tmpint].setAmountCheckedout(books[tmpint].getAmountCheckedout() + 1);
			out << "Book " << books[tmpint].getName() << " is checked out" << endl << endl;
		}
		else out << "All books are checked out earlier." << endl << endl;
	}

	void howManyBooksGiven(ostream& out) const
	{
		out << "SEVENTH TASK:" << endl;

		double percentage = 0;
		for (size_t i = 0; i < books.size(); i++)
			if (books[i].getAmountCheckedout() == books[i].getAmountAvailable())
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
	for (size_t i = 0; i < lib.books.size(); i++)
		out << lib.books[i] << endl;

	return out;
}

int main()
{
	Library lib("Name", Specialization("City", "Street", 5), { Book("Name", 2005, 520, 520) });

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