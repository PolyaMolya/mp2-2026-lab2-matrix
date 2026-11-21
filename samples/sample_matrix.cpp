// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц (интерактивный режим)

#include <iostream>
#include "tmatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите размерность квадратных матриц (n): ";
    cin >> n;

    TDynamicMatrix<int> a(n), b(n);
    cout << "Введите элементы матрицы A (" << n << "x" << n << "):\n";
    cin >> a;
    cout << "Введите элементы матрицы B (" << n << "x" << n << "):\n";
    cin >> b;
    cout << "\nМатрица A:\n" << a;
    cout << "\nМатрица B:\n" << b;
    cout << "\nСложение (A + B):\n" << (a + b);
    cout << "\nВычитание (A - B):\n" << (a - b);
    cout << "\nУмножение (A * B):\n" << (a * b);
    int k;
    cout << "\nВведите скаляр k для умножения матрицы A: ";
    cin >> k;
    cout << "\nA * " << k << ":\n" << (a * k);

    TDynamicVector<int> v(n);
    cout << "\nВведите вектор v размера " << n << ":\n";
    cin >> v;
    cout << "\nУмножение матрицы A на вектор v (A * v):\n" << (a * v) << endl;
    system("pause");
    return 0;
}