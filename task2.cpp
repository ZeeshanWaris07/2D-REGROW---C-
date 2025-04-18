#include<iostream>
#include<fstream>
using namespace std;

void Copydata(const char Filename[], const char Copyfile[])
{
	ifstream fin(Filename);
	ofstream fout(Copyfile);
	if (fin)
	{
		char a;
		while (fin.get(a))
		{
			if (fout)
			{
				fout << a;
			}
		}
	}
	fin.close();
}

void Copy(char* Arr, char* temp, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = Arr[i];
	}
}

char* Regrow(char* Arr, int size)
{
	char* temp = new char[size];
	Copy(Arr, temp, size);
	delete[] Arr;
	return temp;
}

int Compare(char* Arr, char* Arr1, int size)
{
	int count = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (Arr[i] == Arr1[i])
		{
			count++;
		}
	}
	return count;
}

void Write(char* Arr, int size, int maincount)
{
	bool flag = true;
	ifstream fin("wordfrequency.txt");
	if (fin)
	{
		int size2 = 1;
		char* Arr2 = new char[size2];
		while (fin.get(Arr2[size2 - 1]))
		{
			if (Arr2[size2 - 1] != ' ')
			{
				if (Arr2[size2 - 1] == '\n')
				{
					size2 = 1;
					delete[] Arr2;
					Arr2 = new char[size2];
				}
				else
				{
					size2++;
					Arr2 = Regrow(Arr2, size2);
				}
			}
			else
			{
				int temp;
				fin >> temp;
				Arr2[size2 - 1] = '\0';
				int count = Compare(Arr, Arr2, size);
				if (count == size - 1)
				{
					flag = false;
					break;
				}
			}
		}
		delete[] Arr2;
		Arr2 = NULL;
		size2 = 1;
		Arr2 = new char[size2];
	}
	fin.close();

	if (flag == true)
	{
		ofstream fout("wordfrequency.txt", ios::app);
		if (fout)
		{
			fout << Arr << " " << maincount << endl;
			cout << Arr << " " << maincount << endl;
		}
	}
}

void Check(char* Arr, int size, int& maincount)
{
	ifstream fin1("output.txt");
	if (fin1)
	{
		int size1 = 1;
		char* Arr1 = new char[size1];
		while (fin1.get(Arr1[size1 - 1]))
		{
			if (Arr1[size1 - 1] != '\n')
			{
				size1++;
				Arr1 = Regrow(Arr1, size1);
			}
			else
			{
				Arr1[size1 - 1] = '\0';
				int count = Compare(Arr, Arr1, size);
				if (count == size - 1)
				{
					maincount++;
				}
				delete[] Arr1;
				size1 = 1;
				Arr1 = new char[size1];
			}
		}
		fin1.close();
		delete[] Arr1;
		Arr1 = NULL;
	}
}

void Readfile(const char Filename[], const char Copyfile[])
{
	ifstream fin(Filename);
	if (fin)
	{
		int size = 1;
		char* Arr = new char[size];
		while (fin.get(Arr[size - 1]))
		{
			if (Arr[size - 1] != '\n')
			{
				size++;
				Arr = Regrow(Arr, size);
			}
			else
			{
				int maincount = 0;
				Arr[size - 1] = '\0';
				Check(Arr, size, maincount);
				Write(Arr, size, maincount);
				delete[] Arr;
				size = 1;
				Arr = new char[size];
			}
		}
		fin.close();
		delete[] Arr;
		Arr = NULL;
	}
}

int main()
{
	Copydata("word.txt", "output.txt");
	Readfile("word.txt", "output.txt");
}