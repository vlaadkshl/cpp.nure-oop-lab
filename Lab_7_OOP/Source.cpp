#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
class Array2D
{
public:
	class ArraylD
	{
	private:
		size_t dim2;
		T* Array1;

	public:
		friend class Array2D;

		ArraylD() :Array1(NULL), dim2(0) {}

		T& operator[](int index)
		{
			return Array1[index];
		}

		const T& operator[] (int index) const
		{
			return Array1[index];
		}

		ArraylD& operator=(ArraylD& elem)
		{
			if (this == &elem)
				return *this;

			dim2 = elem.dim2;
			Array1 = elem.Array1;

			return *this;
		}
	};

private:
	size_t dim1;
	ArraylD* Array2;
public:
	Array2D() : dim1(0), Array2(NULL) {}
	Array2D(size_t d1, size_t d2) : dim1(d1)
	{
		Array2 = new ArraylD[dim1];

		for (int i = 0; i < d1; ++i)
		{
			Array2[i].dim2 = d2;
			Array2[i].Array1 = new T[d2];
		}
	}
	virtual ~Array2D()
	{
		for (int i(0); i < dim1; ++i)
			delete[]Array2[i].Array1;
		delete[] Array2;
	}

	ArraylD& operator[] (int index)
	{
		return Array2[index];
	}
	const ArraylD& operator[] (int index) const
	{
		return Array2[index];
	}
};

//	Переставити рядки матриці відповідно до зростання елементів другого стовпця
int main()
{
	srand(static_cast<unsigned int>(time(0)));

	const size_t n = 3, m = 4;

	Array2D<int> array2D(n, m);

	for (int i = 0; i < n; cout << endl, ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			array2D[i][j] = rand() % 11;
			cout << array2D[i][j] << '\t';
		}
	}
	cout << endl << endl;

	size_t row_index[n];
	int elem_2nd_column[n];

	for (size_t i = 0; i < n; i++)
	{
		row_index[i] = i;
		elem_2nd_column[i] = array2D[i][1];
	}

	cout << "Row / Elem of 2nd column of that row:\n";
	for (size_t i = 0; i < n; i++)
		cout << row_index[i] << ": " << elem_2nd_column[i] << "\t";
	cout << endl << endl;

	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = 0; j < n - 1 - i; j++)
		{
			if (elem_2nd_column[j + 1] < elem_2nd_column[j])
			{
				swap(elem_2nd_column[j], elem_2nd_column[j + 1]);
				swap(row_index[j], row_index[j + 1]);
			}
		}
	}
	cout << "Sorted!\n\n";

	cout << "Row / Elem of 2nd column of that row:\n";
	for (size_t i = 0; i < n; i++)
		cout << row_index[i] << ": " << elem_2nd_column[i] << "\t";
	cout << endl << endl;

	for (int i = 0; i < n; cout << endl, ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cout << array2D[row_index[i]][j] << '\t';
		}
	}

	return 0;
}