// Дана матрица размером n*n. Выполнить транспонирование матриц.
// Выполнить задание на динамическом массиве 

#include<iostream>
using namespace std;


int** create(int& n);
void input(int& m, int** a);
void random_input(int n, int** a);
void output(int m, int** a);
void T(int n, int** a);

int main()
{
	int size;
	int** arr = create(size);
	cout << "Zapolnenie sluchyaynymi chislami: \n";
	random_input(size, arr);
	output(size, arr);
	cout << "Transponirovannaya matrica: \n";
	T(size, arr);
	output(size, arr);
	cout << "_____________________________________\n" << "Zapolnite matricu: \n";
	input(size, arr);
	cout << "Transponirovannaya matrica: \n";
	T(size, arr);
	output(size, arr);
	return 0;
}




int** create(int& n) // Создание 
{
	cout << "Vvedite razmer matricy: ";
	cin >> n;
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	return a;
}

void input(int& m, int** a) // Заполнение 
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "a[" << i+1 << "][" << j+1 << "] = ";
			cin >> a[i][j];
		}
	}
}

void random_input(int n, int** a) // Заполнение случайными числами от -50 до 50
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = rand() % 101 - 50;
		}
	}
}

void output(int m, int** a)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "a[" << i+1 << "][" << j+1 << "] = " << a[i][j] << '\n';
		}
	}
}

void T(int n, int** a) // Транспортирование матриц
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
		}
	}
}