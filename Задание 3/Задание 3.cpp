// Два выпуклых многоугольника на плоскости заданы координатами вершин в порядке обхода границы. 
// Определить площадь многоугольника и определить, вложены ли они.
#include <iostream>
#include <vector>
using namespace std;

float S(vector <vector <int>>& a, int n);
int search_point(vector <vector <int>>& a, int n);
void input(vector <vector <int>>& a, int n);
void output(vector <vector <int>>& a, int n);
float angle(int x0, int y0, int x, int y);
bool tri_check(vector <vector <int>>& a, int p1, int p2, int p3, int x, int y);
bool check(vector <vector <int>>& a, int n, int x, int y);
bool check_in(vector <vector <int>>& a, int na, vector <vector <int>>& b, int nb);
void ans(vector <vector <int>>& a, int na, vector <vector <int>>& b, int nb);

int main()
{
	int n1, n2; // Количество точек в 1ом и 2ом многоугольниках соответсвенно 
	cout << "Kol-vo tochek v 1om mnogougol`nike: ";
	cin >> n1;
	vector < vector <int> > figure1(n1);
	for (int i = 0; i < n1; i++)
	{
		figure1[i].resize(2);
	}
	input(figure1, n1);
	cout << "Kol-vo tochek vo 2om mnogougol`nike: ";
	cin >> n2;
	vector < vector <int> > figure2(n2);
	for (int i = 0; i < n2; i++)
	{
		figure2[i].resize(2);
	}
	input(figure2, n2);
	float s1, s2;
	ans(figure1, n1, figure2, n2);
	return 0;
}


float S(vector <vector <int>>& a, int n) // Площадь n-угольника 
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += (a[i][0] + a[(i + 1) % n][0]) * (a[(i + 1) % n][1] - a[i][1]);
	}
	return abs(sum) * 0.5;
}
int search_point(vector <vector <int>>& a, int n) // Поиск точки, с наименьшей координатой x  
{
	int l_x = a[0][0];
	int l_y = a[0][1];
	int index = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i][0] < l_x)
		{
			l_x = a[i][0];
			l_y = a[i][1];
			index = i;
		}
		if (a[i][0] == l_x) // Если несколько точек с min координатой x, выбираем из них самую "низкую"
		{
			if (a[i][1] < l_y)
			{
				l_x = a[i][0];
				l_y = a[i][1];
				index = i;
			}
		}
	}
	return index;
}
void input(vector <vector <int>>& a, int n) // Заполнение массива 
{
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i << " = ";
		cin >> a[i][0];
		cout << "y" << i << " = ";
		cin >> a[i][1];
	}
}
void output(vector <vector <int>>& a, int n) // Вывод массива 
{
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i << " = " << a[i][0] << "   ";
		cout << "y" << i << " = " << a[i][1] << "\n";
	}
}
float angle(int x0, int y0, int x, int y) // Находит полярный угол относительно точки o(x0, y0)
{
	return (float)(y - y0) / (float)(x - x0);
}
bool tri_check(vector <vector <int>>& a, int p1, int p2, int p3, int x, int y) // Проверка принадлежности точки p(x, y) треугольнику p1p2p3
{
	int q1 = (a[p2][0] - a[p1][0]) * (y - a[p1][1]) - (a[p2][1] - a[p1][1]) * (x - a[p1][0]); // Модуль векторного произведения [p1p2, p1p]
	int q2 = (a[p3][0] - a[p2][0]) * (y - a[p2][1]) - (a[p3][1] - a[p2][1]) * (x - a[p2][0]); // Модуль векторного произведения [p2p3, p2p]
	int q3 = (a[p1][0] - a[p3][0]) * (y - a[p3][1]) - (a[p1][1] - a[p3][1]) * (x - a[p3][0]); // Модуль векторного произведения [p3p1, p3p]
	return ((q1 >= 0 && q2 >= 0 && q3 >= 0) || (q1 <= 0 && q2 <= 0 && q3 <= 0)); // Точка принадлежит, если 3 модуля век. про-ий ОДНОВРЕМЕННО неотрицательные/неположительные
}
bool check(vector <vector <int>>& a, int n, int x, int y) // Проверяет принадлежит ли точка  p(x, y) фигуре 
{
	int p1, p2;
	float r1, r2;
	int o = search_point(a, n);
	if (a[o][0] == x && a[o][1] == y) // Рассматриваем исключительный случай, когда точки p и o совпадают 
	{
		return true;
	}
	float r = angle(a[o][0], a[o][1], x, y); // Полярный угол точки p относительно точки о
	for (int i = 1; i < n - 1; i++)
	{
		r1 = angle(a[o][0], a[o][1], a[(i + o) % n][0], a[(i + o) % n][1]);
		r2 = angle(a[o][0], a[o][1], a[(i + o + 1) % n][0], a[(i + o + 1) % n][1]);
		if ((r <= r1 && r >= r2) || (r <= r2 && r >= r1)) // Ищем две соседние точки, между полярными углами который будет лежать полярный угол точки p
		{
			p1 = (i + o) % n;
			p2 = (i + o + 1) % n;
			return tri_check(a, o, p1, p2, x, y); // Определяем принадлежность точки p треугольнику op1p2
		}
	}
	return false;
}
bool check_in(vector <vector <int>>& a, int na, vector <vector <int>>& b, int nb) // Проверяет вложенность многоугольников
{
	for (int i = 0; i < nb; i++)
	{
		if (check(a, na, b[i][0], b[i][1]) == 0)
		{
			return false; // Если хотя бы одна точка второго многоугольника не принадлежит 1му => нея являются вложенными
		}
	}
	return true;
}

void ans(vector <vector <int>>& a, int na, vector <vector <int>>& b, int nb) // Вывод ответа
{
	float sq1 = S(a, na);
	float sq2 = S(b, nb);
	cout << "Ploshchad` 1go mnogougol`nika: " << sq1 << '\n';
	cout << "Ploshchad` 2go mnogougol`nika: " << sq2 << '\n';
	if (check_in(a, na, b, nb) || check_in(b, nb, a, na))
	{
		if (sq1 < sq2)
		{
			cout << "1yj mnogougol'nik yavlyaetsya vlozhennym vo 2oj";
		}
		if (sq1 == sq2)
		{
			cout << "Mnogougol'niki sovpadayut";
		}
		if (sq1 > sq2)
		{
			cout << "2oj mnogougol'nik yavlyaetsya vlozhennym v 1yj";
		}
	}
	else
	{
		cout << "Mnogougol`niki ne yavlyayutsya vlozhennymi";
	}
}