#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	size_t n;
	cout << "Enter number of rows/columns: ";
	while (true)
	{
		string tmpstr;
		int tmpint;
		cin >> tmpstr;
		tmpint = atoi(tmpstr.c_str());

		if (tmpint > 0)
		{
			n = tmpint;
			break;
		}
	}

	vector<vector<int>> array(n, vector<int>(n));
	cout << "Enter elements (divide them by ';')" << endl;
	for (size_t i = 0; i < n; i++)
	{
		string tmpstr;
		cin >> tmpstr;
		istringstream strstream(tmpstr);

		for (size_t j = 0; j < n; j++)
		{
			string tmp;
			getline(strstream, tmp, ';');
			array[i][j] = atoi(tmp.c_str());
		}
	}

	cout << "YOUR ARRAY:" << endl;
	for (size_t i = 0; i < n; i++, cout << endl)
		for (size_t j = 0; j < n; j++)
			cout << array[i][j] << "\t";

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			int minelem = array[i][0];
			for (size_t j = 0; j < n; j++)
				if (array[i][j] < minelem)
					minelem = array[i][j];

			for (size_t j = 0; j < n; j++)
				if (j < i && array[i][j] < 0)
					array[i][j] = minelem;
		}
	}

	cout << "RESULT ARRAY:" << endl;
	for (size_t i = 0; i < n; i++, cout << endl)
		for (size_t j = 0; j < n; j++)
			cout << array[i][j] << "\t";

	cout << "RESULT OUTPUT:" << endl;
	for (size_t j = 0; j < n; j++)
	{
		for (int i = n - 1; i >= 0; i--)
			cout << array[i][j] << "\t";
		cout << endl;
	}

	system("pause");
	return 0;
}