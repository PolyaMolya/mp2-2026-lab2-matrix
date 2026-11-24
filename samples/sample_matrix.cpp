// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

int main()
{
    int n1, n2, n3;
    double k;

    cout << "Matrix test application" << endl;
    cout << "Enter size of matrix A: ";
    cin >> n1;
    cout << "Enter size of matrix B: ";
    cin >> n2;
    cout << "Enter size of vector: ";
    cin >> n3;

    try
    {
        // если размер некорректный, то конструктор бросит исключение
        TDynamicMatrix<double> a(n1), b(n2), c(n1);
        TDynamicVector<double> v(n3);

        cout << "Enter matrix A (" << n1 * n1 << " numbers):" << endl;
        cin >> a;
        cout << "Enter matrix B (" << n2 * n2 << " numbers):" << endl;
        cin >> b;
        cout << "Enter vector v (" << n3 << " numbers):" << endl;
        cin >> v;
        cout << "Enter a number k: ";
        cin >> k;

        if (!cin)
        {
            cout << "Input error" << endl;
            return 1;
        }

        cout << endl << "Matrix A =" << endl << a;
        cout << "Matrix B =" << endl << b;

        try
        {
            c = a + b;
            cout << endl << "A + B =" << endl << c;
        }
        catch (const exception& e)
        {
            cout << endl << "A + B: error, " << e.what() << endl;
        }

        try
        {
            c = a - b;
            cout << endl << "A - B =" << endl << c;
        }
        catch (const exception& e)
        {
            cout << endl << "A - B: error, " << e.what() << endl;
        }

        try
        {
            c = a * b;
            cout << endl << "A * B =" << endl << c;
        }
        catch (const exception& e)
        {
            cout << endl << "A * B: error, " << e.what() << endl;
        }

        try
        {
            TDynamicVector<double> r = a * v;
            cout << endl << "A * v = " << r << endl;
        }
        catch (const exception& e)
        {
            cout << endl << "A * v: error, " << e.what() << endl;
        }

        try
        {
            TDynamicVector<double> r = b * v;
            cout << endl << "B * v = " << r << endl;
        }
        catch (const exception& e)
        {
            cout << endl << "B * v: error, " << e.what() << endl;
        }

        c = a * k;
        cout << endl << "A * k =" << endl << c;
        c = b * k;
        cout << endl << "B * k =" << endl << c;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

/*void main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
}*/
//---------------------------------------------------------------------------
