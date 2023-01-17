#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <math.h>

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
	string getStreet() const { return street; }
	size_t getNumber() const { return number; }

	void setCity(string city) { this->city = city; }
	void setStreet(string street) { this->street = street; }
	void setNumber(size_t number) { this->number = number; }

	~Specialization() {}
};
ostream& operator<<(ostream& out, const Specialization& spec)
{
	out << spec.getCity() << ", " << spec.getStreet() << " str., " << spec.getNumber();
	return out;
}
istream& operator>>(istream& in, Specialization& spec)
{
	string tmp;

	//	Місто
	getline(in, tmp, ',');
	spec.setCity(tmp);

	//	Вулиця
	getline(in, tmp, ',');
	spec.setStreet(tmp);

	//	Номер будинку
	getline(in, tmp);
	spec.setNumber(atoi(tmp.c_str()));

	return in;
}

class Book
{
	string name;
	int year;
	size_t amount_available, amount_checkedout;
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
	int getYear() const { return year; }
	size_t getAmountAvailable() const { return amount_available; }
	size_t getAmountCheckedout() const { return amount_checkedout; }

	void setName(string name) { this->name = name; }
	void setYear(size_t year) { this->year = year; }
	void setAmountAvailable(size_t amount) { amount_available = amount; }
	void setAmountCheckedout(size_t amount) { amount_checkedout = amount; }

	~Book() {}
};
ostream& operator<<(ostream& out, const Book& book)
{
	out << book.getName() << " (" << book.getYear() << "):" << endl;
	out << "\tAvailable: " << book.getAmountAvailable() << endl;
	out << "\tPublished: " << book.getAmountCheckedout() << endl;
	return out;
}
istream& operator>>(istream& in, Book& book)
{
	string tmp;

	//	Назва книги
	getline(in, tmp, ',');
	book.setName(tmp);

	//	Рік видання
	getline(in, tmp, ',');
	(atoi(tmp.c_str()) <= 2022)
		? book.setYear(atoi(tmp.c_str()))
		: book.setYear(2022);

	//	Доступно книг всього
	getline(in, tmp, ',');
	(atoi(tmp.c_str()) > 0)
		? book.setAmountAvailable(atoi(tmp.c_str()))
		: book.setAmountAvailable(0);

	//	Виписано книг вже
	getline(in, tmp, '_');
	(book.getAmountAvailable() > atoi(tmp.c_str()))
		? book.setAmountCheckedout(atoi(tmp.c_str()))
		: book.setAmountCheckedout(book.getAmountAvailable());

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

	bool operator<(const Library b) const
	{
		if (this->specialization.getStreet() == b.specialization.getStreet())
			return this->specialization.getNumber() < b.specialization.getNumber();
		else
			return this->specialization.getStreet() < b.specialization.getStreet();
	}

	bool operator==(const Library& a)
	{
		return (name == a.name
			&& specialization.getCity() == a.specialization.getCity()
			&& specialization.getNumber() == a.specialization.getNumber()
			&& specialization.getStreet() == a.specialization.getStreet());
	}

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
ostream& operator<<(ostream& out, const Library& lib)
{
	out << "=== Library: " << lib.getName() << " ===\n";
	out << "Adress:\t" << lib.specialization << endl;
	for (size_t i = 0; i < lib.books.size(); i++)
		out << i + 1 << ".\t" << lib.books[i];

	return out;
}
istream& operator>>(istream& in, Library& lib)
{
	/*
		БІБЛІОТЕКА:Київ,Хрещатик,1;Книга1,2004,120,1_Книга2,2021,10,9_Книга3,2020,850,4
	*/
	string tmp;

	//	Назва
	getline(in, tmp, ':');
	lib.setName(tmp);

	//	Адреса
	getline(in, tmp, ';');
	stringstream tmp_spec(tmp);
	tmp_spec >> lib.specialization;

	//	Масив книг
	getline(in, tmp);
	vector<Book> tmp_vector;
	stringstream tmp_books(tmp);
	copy(istream_iterator<Book>(tmp_books), istream_iterator<Book>(), back_inserter(tmp_vector));
	lib.books = tmp_vector;

	return in;
}

void print_task(ostream& out, size_t n)
{
	out << ":::::::::::::::::::::::TASK " << n << ":::::::::::::::::::::::" << endl;
}

//	Для завдання 2:
bool compare_by_books(const Library& a, const Library& b)
{
	return a.books.size() < b.books.size();
}
//	Для завдання 3:
bool more_4_books(const Library& a)
{
	return (a.books.size() >= 4);
}
//	Для завдання 6:
int average_books_num(size_t sum, const Library& a)
{
	return sum += a.books.size();
}
//	Для завдання 7:
bool sub_vector_search(Library& a, Library& b)
{
	return a == b;
}

int main()
{
	vector<Library> libs;

	/*
		TASK 1:
		Забезпечити для контейнера можливість зчитування з файлу і запису в файл з використанням ітераторів потоків.
	*/
	//	Зчитування
	print_task(cout, 1);
	ifstream fin("input.txt");
	if (!fin) { cerr << "File not found"; return -1; }
	copy(istream_iterator<Library>(fin), istream_iterator<Library>(), back_inserter(libs));
	fin.close();
	
	//	Запис
	ofstream fout("output.txt");
	copy(libs.begin(), libs.end(), ostream_iterator<Library>(fout, "\n"));
	copy(libs.begin(), libs.end(), ostream_iterator<Library>(cout, "\n"));
	cout << endl;
	
	/*
		TASK 2:
		СОРТУВАННЯ:
		1.	За вулицею і номером будинку (за замовчуванням);
		2.	За кількістю книг.
	*/
	print_task(cout, 2);
	//	За вулицею і номером будинку
	cout << "Sorted by adress:\n";
	sort(libs.begin(), libs.end());
	copy(libs.begin(), libs.end(), ostream_iterator<Library>(cout, "\n"));
	//	За кількістю книг
	cout << "Sorted by number of books:\n";
	sort(libs.begin(), libs.end(), compare_by_books);
	copy(libs.begin(), libs.end(), ostream_iterator<Library>(cout, "\n"));
	cout << endl;

	/*
		TASK 3:
		Винести в окремий вектор всі бібліотеки, починаючи з тої, в якій більше 4 книг.
	*/
	print_task(cout, 3);
	vector<Library>::iterator it = find_if(libs.begin(), libs.end(), more_4_books);
	vector<Library> task_3;
	copy(it, libs.end(), back_inserter(task_3));
	copy(task_3.begin(), task_3.end(), ostream_iterator<Library>(cout, "\n"));
	cout << endl;

	/*
		TASK 4:
		Зберегти всі номери будинків бібліотек з вектора (3) в окремому векторі.
	*/
	print_task(cout, 4);
	vector<size_t> task_4;
	transform(task_3.begin(),
		task_3.end(),
		back_inserter(task_4),
		[](const Library& a) { return a.specialization.getNumber(); });
	copy(task_4.begin(), task_4.end(), ostream_iterator<size_t>(cout, "\t"));
	cout << endl;
	cout << endl;

	/*
		TASK 5:
		Дізнатися, скільки в векторі з кроку 4 номерів будинків більших від заданого.
	*/
	print_task(cout, 5);
	size_t task_5 = count_if(task_4.begin(), task_4.end(), bind2nd(greater<size_t>(), 10));
	cout << "Number of buildings that are bigger than 10: " << task_5 << endl;
	cout << endl;

	/*
		TASK 6:
		Знайти середню кількість книг у всіх бібліотеках з використанням accumulate()
	*/
	print_task(cout, 6);
	size_t task_6 = accumulate(libs.begin(), libs.end(), 0, average_books_num) / libs.size();
	cout << "Average number of books for libraries: " << task_6 << endl;
	cout << endl;

	/*
		TASK 7:
		Перевірити, чи входить вектор, отриманий на кроці 3, в вихідний вектор як підпослідовність.
	*/
	print_task(cout, 7);
	vector<Library>::iterator it_ = search(libs.begin(), libs.end(), task_3.begin(), task_3.end(), sub_vector_search);
	if (it_ != libs.end())
		cout << "Subvector is found!\n";
	else
		cout << "Subvector isn't found.\n";
	cout << endl;

	system("pause");
	return 0;
}