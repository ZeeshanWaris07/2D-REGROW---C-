#include<Iostream>
#include<fstream>
using namespace std;

void DeepCopy(char** Arr,int size1d,int size2d,char* temp)
{
	for (int i = 0; i < size1d - 1; i++)
	{
		temp[i] = Arr[size2d - 1][i];
	}
}

char* Regrow1d(char** Arr, int size1d, int size2d)
{
	char* temp = new char[size1d];
	DeepCopy(Arr, size1d, size2d,temp);
	delete[] Arr[size2d - 1];
	return temp;
}

char** Readfile(char** Arr, int& row)
{
	ifstream fin("input.txt");
	if (fin)
	{
		fin >> row;
		char temp;
		fin.get(temp);
		Arr = new char* [row];
		int size2d = 1, size1d = 1;
		Arr[size2d - 1] = new char[size1d];
		while (fin.get(Arr[size2d - 1][size1d - 1]))
		{
			if (Arr[size2d - 1][size1d - 1] != '\n')
			{
				if (Arr[size2d - 1][size1d - 1] != ' ')
				{
					size1d++;
					Arr[size2d - 1] = Regrow1d(Arr, size1d, size2d);
				}
			}
			else
			{
				Arr[size2d - 1][size1d - 1] = '\0';
				size2d++;
				size1d = 1;
				Arr[size2d - 1] = new char[size1d];
			}
		}
	}
	return Arr;
}

void Substringinput(char Substring[])
{
	cout << "Enter the Substring : ";
	cin >> Substring;
}

int Sizecalculator(char Substring[])
{
	int size = 0;
	for (int i = 0; Substring[i] != '\0'; i++)
	{
		size++;
	}
	return size;
}
void Write(int i, int j, int c)
{
	cout << "Found at row " << i << " Starting coloumn " << j << " Ending coloumn " << c - 1 << endl;
}

void Wordsearch(char** Arr, int row, int subsize, char Substring[])
{
	int count = 0;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; Arr[i][j] != '\0'; j++)
		{
			if (Arr[i][j] == Substring[0])
			{
				int r = i, c = j, checkcount = 0;
				for (int k = 0; k < subsize; k++)
				{
					if (Arr[r][c] == Substring[k])
					{
						checkcount++;
						c++;
					}
				}
				if (checkcount == subsize)
				{
					Write(i, j, c);
				}
			}
		}
	}
}

int main()
{
	int row = 0;
	char** Arr = NULL;
	Arr = Readfile(Arr, row);
	char Substring[10];
	Substringinput(Substring);
	int subsize = Sizecalculator(Substring);
	Wordsearch(Arr, row, subsize, Substring);
	
	for (int i = 0; i < row; i++)
	{
		delete[] Arr[i];
	}

	delete[] Arr;
	Arr = NULL;
}