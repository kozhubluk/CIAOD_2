// Дана матрица размером n*n. Выполнить транспонирование матриц.
// Выполнить задание на статическом массиве


#include <iostream>
using namespace std;
const int rows = 10;
const int cols = 10;

void input(int arr[][cols], int n);
void random_input(int arr[][cols], int n);
void output(int arr[rows][cols], int n);
void T(int(*arr)[cols], int n);

int main()
{
    int size;
    int matrix[rows][cols];
    do
    {
        cout << "Vvedite razmer maticy: ";
        cin >> size;
    } while (size > 10); // Проверяем, чтобы размер матрицы не был больше допустимого (10)
    cout << "Zapolnenie matricy skuchyaynymi chislami: \n";
    random_input(matrix, size);
    output(matrix, size);
    T(matrix, size);
    cout << "Transponirovanie matricy: \n";
    output(matrix, size);
    cout << "_______________________________________________\n";
    cout << "Zapolnite matricu: \n";
    input(matrix, size);
    T(matrix, size);
    cout << "Transponirovanie matricy: \n";
    output(matrix, size);
    return 0;
}

void input(int arr[][cols], int n) // Заполнение матрицы пользователем 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> arr[i][j];
        }
    }
}
void random_input(int arr[][cols], int n) // Заполнение случайными числами от -50 до 50
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 101 - 50;
        }
    }
}

void output(int arr[rows][cols], int n) // Вывод матрицы построчно 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = " << arr[i][j] << "\n";
        }
    }
}
void T(int(*arr)[cols], int n) // Транспортирование матриц
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}