#include<iostream>
#include<fstream>

using namespace std;


void InputFilename(char Filename[])
{
	cout << "Enter Filename : ";
	cin >> Filename;
}

int* Readfile(char Filename[], int& size)
{
	ifstream fin(Filename);
	if (fin)
	{
		fin >> size;
		int* Arr = new int[size];
		for (int i = 0; i < size; i++)
		{
			fin >> Arr[i];
		}
		fin.close();
		return Arr;
	}
}

void Copy(int* Arr, int* temp, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = Arr[i];
	}
}

int* Regrow(int* Arr, int size)
{
	int* temp = new int[size];
	Copy(Arr, temp, size);
	delete[] Arr;
	return temp;
}

void Write(int* Even, int* Odd, int size1, int size2)
{
	cout << "Even numbers : ";
	for (int i = 0; i < size1 - 1; i++)
	{
		cout << Even[i] << " ";
	}
	cout << endl;
	cout << "Odd numbers : ";
	for (int i = 0; i < size2 - 1; i++)
	{
		cout << Odd[i] << " ";
	}
}

void Check(int* Arr, int size)
{
	int size1 = 1, size2 = 1;
	int* Even = new int[size1];
	int* Odd = new int[size2];
	for (int i = 0; i < size; i++)
	{
		if (Arr[i] % 2 == 0)
		{
			Even[size1 - 1] = Arr[i];
			size1++;
			Even = Regrow(Even, size1);
		}
		else
		{
			Odd[size2 - 1] = Arr[i];
			size2++;
			Odd = Regrow(Odd, size2);
		}
	}

	Write(Even, Odd, size1, size2);
	delete[] Even;
	Even = NULL;
	delete[] Odd;
	Odd = NULL;
}

int main()
{
	int size;
	char Filename[20];
	InputFilename(Filename);
	int* Arr = Readfile(Filename, size);
	Check(Arr, size);

	delete[] Arr;
	Arr = NULL;
}