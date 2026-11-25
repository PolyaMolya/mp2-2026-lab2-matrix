// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tmatrix.h"
//---------------------------------------------------------------------------
using namespace std;

template<typename T>
void fillRandom(TDynamicMatrix<T>& m)
{
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m.size(); j++)
            m[i][j] = rand() % 20 - 10; // случайные числа от -10 до 9
}

 int main()
{
  setlocale(LC_ALL, "Russian");
  srand(static_cast<unsigned int>(time(nullptr)));
  cout << "Тестирование класс работы с матрицами ";
      try
      {
          size_t n;
          cout << "Введите размерность квадратных матриц (от 1 до " << MAX_MATRIX_SIZE << "): ";
          if (!(cin >> n))
          {
              cout << "Ошибка ввода размерности." << endl;
              return 1;
          }

          TDynamicMatrix<int> a(n), b(n);

          int fillChoice = 0;
          cout << "\nВыберите способ заполнения матриц:\n"
              << "1 - Ввод с клавиатуры\n"
              << "2 - Заполнение случайными числами\n"
              << "Ваш выбор: ";
          cin >> fillChoice;

          if (fillChoice == 1)
          {
              cout << "Введите элементы матрицы A (" << n << "x" << n << "):" << endl;
              cin >> a;
              cout << "Введите элементы матрицы B (" << n << "x" << n << "):" << endl;
              cin >> b;
          }
          else
          {
              fillRandom(a);
              fillRandom(b);
          }

          int op = -1;
          while (op != 0)
          {
              cout << "\n Текущие матрицы \n";
              cout << "Матрица A:\n" << a;
              cout << "Матрица B:\n" << b;

              cout << "\nВыберите операцию:\n"
                  << "1 - Сложение (A + B)\n"
                  << "2 - Вычитание (A - B)\n"
                  << "3 - Умножение матриц (A * B)\n"
                  << "4 - Умножение матрицы A на число\n"
                  << "5 - Умножение матрицы A на вектор\n"
                  << "6 - Копирование (B = A) и проверка равенства (A == B)\n"
                  << "0 - Выход\n"
                  << "Ваш выбор: ";
              cin >> op;

              switch (op)
              {
              case 1:
                  cout << "\nРезультат A + B:\n" << (a + b);
                  break;
              case 2:
                  cout << "\nРезультат A - B:\n" << (a - b);
                  break;
              case 3:
                  cout << "\nРезультат A * B:\n" << (a * b);
                  break;
              case 4:
              {
                  int scalar;
                  cout << "Введите скаляр: ";
                  cin >> scalar;
                  cout << "\nРезультат A * " << scalar << ":\n" << (a * scalar);
                  break;
              }
              case 5:
              {
                  TDynamicVector<int> v(n);
                  cout << "Введите " << n << " элементов вектора: ";
                  cin >> v;
                  cout << "\nРезультат A * v:\n" << (a * v) << endl;
                  break;
              }
              case 6:
              {
                  b = a;
                  cout << "\nМатрица A скопирована в B.\n";
                  cout << "Проверка (A == B): " << (a == b ? "Равны (true)" : "Не равны (false)") << endl;
                  break;
              }
              case 0:
                  cout << "Завершение работы." << endl;
                  break;
              default:
                  cout << "Неизвестная команда. Попробуйте снова." << endl;
                  break;
              }
          }
      }
      catch (const exception& ex)
      {
          cerr << "\nИсключение: " << ex.what() << endl;
          return 1;
      }

      return 0;
 }
//---------------------------------------------------------------------------
