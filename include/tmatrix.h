// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector{
private:
    size_t sz;
    size_t nz;  // кол-во ненулевых элементов
    size_t* pIn;  // массив индексов ненулевых элементов
    T* pVal;  // массив значений ненулевых элементов
public:
  TDynamicVector(size_t size = 1){ // к-ор по умолчанию
      if (size == 0 || size > MAX_VECTOR_SIZE) {
          throw out_of_range("Vector size should be greater than zero");
      }
      sz = size;
      nz = 0;
      pIn = NULL;
      pVal = NULL;
  }
  TDynamicVector(T* arr, size_t s){
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (s == 0 || s > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
    sz = s;
    int i = 0;
    nz = 0;
    for (i; i < sz; i++) {
        if (arr[i] != 0) {
            nz++;
        }
    }
    if (nz > 0) {
        pIn = (size_t*)malloc(sizeof(size_t) * nz);
        pVal = (T*)malloc(sizeof(T) * nz);
    }
    if (nz == 0) {
        pVal = NULL;
        pIn = NULL;
    }
    i = 0;
    int j = 0;
    for (i; i < sz; i++) {
        if (arr[i] != 0) {
            pIn[j] = i;
            pVal[j] = arr[i];
            j++;
        }
    }
  }
  TDynamicVector(const TDynamicVector& v){ //к-ор копирования
      sz = v.sz;
      nz = v.nz;
      if (nz == 0) {
          pVal = NULL;
          pIn = NULL;
      }
      if (nz > 0) {
          pVal = (T*)malloc(sizeof(T) * nz);
          pIn = (size_t*)malloc(sizeof(size_t) * nz);
          memcpy(pVal, v.pVal, nz * sizeof(T));
          memcpy(pIn, v.pIn, nz * sizeof(size_t));
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept{ //к-ор перемещения
      sz = v.sz;
      nz = v.nz;
      pVal = v.pVal;
      pIn = v.pIn;
      v.pVal = NULL;
      v.pIn = NULL;
      v.sz = 0;
      v.nz = 0;
  }
  ~TDynamicVector(){
      free(pIn);
      free(pVal);
  }
  TDynamicVector& operator=(const TDynamicVector& v){
      if (this == &v) {
          return *this;
      }
      free(pIn);
      free(pVal);
      sz = v.sz;
      nz = v.nz;
      if (nz == 0) {
          pVal = NULL;
          pIn = NULL;
      }
      if (nz > 0) {
          pVal = (T*)malloc(sizeof(T) * nz);
          pIn = (size_t*)malloc(sizeof(size_t) * nz);
          memcpy(pVal, v.pVal, nz * sizeof(T));
          memcpy(pIn, v.pIn, nz * sizeof(size_t));
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept{
      if (this == &v) {
          return *this;
      }
      free(pVal);
      free(pIn);
      sz = v.sz;
      nz = v.nz;
      pVal = v.pVal;
      pIn = v.pIn;
      v.pVal = NULL;
      v.pIn = NULL;
      v.sz = 0;
      v.nz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind){
      int i = 0;
      for (i; i < nz; i++) {
          if (pIn[i] == ind) {
              return pVal[i];
          }
          if (pIn[i] > ind) {
              break;
          }
      }
      nz++;
      pIn = (size_t*)realloc(pIn, sizeof(size_t) * nz);
      pVal = (T*)realloc(pVal, sizeof(T) * nz);
      int j = nz - 1;
      for (j; j > i; j--) {
          pIn[j] = pIn[j - 1];
          pVal[j] = pVal[j - 1];
      }
      pIn[i] = ind;
      pVal[i] = 0;
      return pVal[i];
  }
  T operator[](size_t ind) const{
      int i = 0;
      for (i; i < nz; i++) {
          if (pIn[i] == ind) {
              return pVal[i];
          }
      }
      return 0;
  }
  // индексация с контролем
  T& at(size_t ind){
      if (ind >= sz) {
          throw out_of_range("Index bol'she razmera massiva");
      }
      int i = 0;
      for (i; i < nz; i++) {
          if (pIn[i] == ind) {
              return pVal[i];
          }
          if (pIn[i] > ind) {
              break;
          }
      }
      nz++;
      pIn = (size_t*)realloc(pIn, sizeof(size_t) * nz);
      pVal = (T*)realloc(pVal, sizeof(T) * nz);
      for (int j = nz - 1; j > i; j--) {
          pIn[j] = pIn[j - 1];
          pVal[j] = pVal[j - 1];
      }
      pIn[i] = ind;
      pVal[i] = 0;
      return pVal[i];
  }
  T at(size_t ind) const{
      if (ind >= sz) {
          throw out_of_range("Index bol'she razmera massiva");
      }
      int i = 0;
      for (i; i < nz; i++) {
          if (pIn[i] == ind) {
              return pVal[i];
          }
      }
      return 0;
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept{
      if (sz != v.sz || nz != v.nz) {
          return false;
      }
      int i = 0;
      for (i; i < nz; i++) {
          if (pIn[i] != v.pIn[i] || pVal[i] != v.pVal[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept{
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val){
      if (val == 0) {
          return TDynamicVector(*this);
      }
      T* tmp = (T*)malloc(sizeof(T) * sz);
      int i = 0;
      for (i; i < sz; i++) {
          tmp[i] = val;
      }
      i = 0;
      for (i; i < nz; i++) {
          tmp[pIn[i]] += pVal[i];
      }
      TDynamicVector res(tmp, sz);
      free(tmp);
      return res;
  }
  TDynamicVector operator-(T val){
      if (val == 0) {
          return TDynamicVector(*this);
      }
      T* tmp = (T*)malloc(sizeof(T) * sz);
      int i = 0;
      for (i; i < sz; i++) {
          tmp[i] = -val;
      }
      i = 0;
      for (i; i < nz; i++) {
          tmp[pIn[i]] += pVal[i];
      }
      TDynamicVector res(tmp, sz);
      free(tmp);
      return res;
  }
  TDynamicVector operator*(T val){
      if (val == 0 || nz == 0) {
          return TDynamicVector(sz);
      }
      TDynamicVector res(*this);
      int i = 0;
      for (i; i < res.nz; i++) {
          res.pVal[i] *= val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v){
      if (sz != v.sz) {
          throw out_of_range("razmeri massivov ne sovpadayut");
      }
      if (nz == 0) return TDynamicVector(v);
      if (v.nz == 0) return TDynamicVector(*this);
      size_t* tmpIn = (size_t*)malloc(sizeof(size_t) * (nz + v.nz));
      T* tmpVal = (T*)malloc(sizeof(T) * (nz + v.nz));
      int k = 0, i = 0, j = 0;
      while (i < nz && j < v.nz) {
          if (pIn[i] < v.pIn[j]) {
              tmpIn[k] = pIn[i];
              tmpVal[k] = pVal[i];
              i++;
              k++;
          }
          else if (pIn[i] > v.pIn[j]) {
              tmpIn[k] = v.pIn[j];
              tmpVal[k] = v.pVal[j];
              j++;
              k++;
          }
          else if (pIn[i] == v.pIn[j]) {
              T sum = pVal[i] + v.pVal[j];
              if (sum != 0) {
                  tmpIn[k] = pIn[i];
                  tmpVal[k] = sum;
                  k++;
              }
              i++;
              j++;
          }
      }
      while (i < nz) {
          tmpIn[k] = pIn[i];
          tmpVal[k] = pVal[i];
          i++;
          k++;
      }
      while (j < v.nz) {
          tmpIn[k] = v.pIn[j];
          tmpVal[k] = v.pVal[j];
          j++;
          k++;
      }
      TDynamicVector res(sz);
      if (k > 0) {
          res.nz = k;
          res.pIn = (size_t*)realloc(tmpIn, sizeof(size_t) * k);
          res.pVal = (T*)realloc(tmpVal, sizeof(T) * k);
      }
      else {
          free(tmpIn);
          free(tmpVal);
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v){
      if (sz != v.sz) {
          throw out_of_range("razmeri massivov ne sovpadayut");
      }
      if (v.nz == 0) return TDynamicVector(*this);
      if (nz == 0) {
          TDynamicVector res(v);
          for (size_t i = 0; i < res.nz; i++) {
              res.pVal[i] = -res.pVal[i];
          }
          return res;
      }
      size_t* tmpIn = (size_t*)malloc(sizeof(size_t) * (nz + v.nz));
      T* tmpVal = (T*)malloc(sizeof(T) * (nz + v.nz));
      int k = 0, i = 0, j = 0;
      while (i < nz && j < v.nz) {
          if (pIn[i] < v.pIn[j]) {
              tmpIn[k] = pIn[i];
              tmpVal[k] = pVal[i];
              i++;
              k++;
          }
          else if (pIn[i] > v.pIn[j]) {
              tmpIn[k] = v.pIn[j];
              tmpVal[k] = -v.pVal[j];
              j++;
              k++;
          }
          else if (pIn[i] == v.pIn[j]) {
              T diff = pVal[i] - v.pVal[j];
              if (diff != 0) {
                  tmpIn[k] = pIn[i];
                  tmpVal[k] = diff;
                  k++;
              }
              i++;
              j++;
          }
      }
      while (i < nz) {
          tmpIn[k] = pIn[i];
          tmpVal[k] = pVal[i];
          i++;
          k++;
      }
      while (j < v.nz) {
          tmpIn[k] = v.pIn[j];
          tmpVal[k] = -v.pVal[j];
          j++;
          k++;
      }
      TDynamicVector res(sz);
      if (k > 0) {
          res.nz = k;
          res.pIn = (size_t*)realloc(tmpIn, sizeof(size_t) * k);
          res.pVal = (T*)realloc(tmpVal, sizeof(T) * k);
      }
      else {
          free(tmpIn);
          free(tmpVal);
      }
      return res;
  }
  T operator*(const TDynamicVector& v) const{
      if (sz != v.sz) {
          throw out_of_range("razmeri massivov ne sovpadayut");
      }
      T sum = 0;
      int i = 0, j = 0;
      while (i < nz && j < v.nz) {
          if (pIn[i] < v.pIn[j]) {
              i++;
          }
          else if (pIn[i] > v.pIn[j]) {
              j++;
          }
          else if (pIn[i] == v.pIn[j]) {
              sum += pVal[i] * v.pVal[j];
              i++;
              j++;
          }
      }
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept{
      size_t tmp_sz = lhs.sz;
      lhs.sz = rhs.sz;
      rhs.sz = tmp_sz;

      size_t tmp_nz = lhs.nz;
      lhs.nz = rhs.nz;
      rhs.nz = tmp_nz;

      size_t* tmp_pIn = lhs.pIn;
      lhs.pIn = rhs.pIn;
      rhs.pIn = tmp_pIn;

      T* tmp_pVal = lhs.pVal;
      lhs.pVal = rhs.pVal;
      rhs.pVal = tmp_pVal;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v){
      T* tmp = (T*)malloc(sizeof(T) * v.sz);
      int i = 0;
      for (i; i < v.sz; i++) {
          istr >> tmp[i];
      }
      v = TDynamicVector(tmp, v.sz);
      free(tmp);
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v){
      int i = 0,j=0;
      for (i; i < v.sz; i++) {
          if (j < v.nz && v.pIn[j] == i) {
              ostr << v.pVal[j] << ' ';
              j++;
          }
          else {
              ostr << 0 << ' ';
          }
      }
      return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix{
private:
    size_t sz;      // размерность квадратной матрицы (sz x sz)
    size_t nz;      // количество ненулевых элементов
    T* pVal;        // значения ненулевых элементов
    size_t* pCol;
    size_t* pRow;
public:
  TDynamicMatrix(size_t s = 1){ // по умолчанию
      if (s == 0 || s > MAX_MATRIX_SIZE) {
          throw out_of_range("Matrix size should be greater than zero and less than MAX_VECTOR_SIZE");
      }
      sz = s;
      nz = 0;
      pVal = NULL;
      pCol = NULL;
      pRow = (size_t*)malloc(sizeof(size_t) * (sz + 1));
      int i = 0;
      for (i; i < sz + 1; i++) {
          pRow[i] = 0;
      }
  }
  TDynamicMatrix(T** arr, size_t s) { 
      assert(arr != nullptr);
      if (s == 0 || s > MAX_MATRIX_SIZE) {
          throw out_of_range("Matrix size should be greater than zero and less than MAX_VECTOR_SIZE");
      }
      sz = s;
      nz = 0;
      int i = 0;
      for (i; i < s; i++) {
          int j = 0;
          for (j; j < s; j++) {
              if (arr[i][j] != 0) {
                  nz++;
              }
          }
      }
      pRow = (size_t*)malloc(sizeof(size_t) * (sz + 1));
      if (nz > 0) {
          pVal = (T*)malloc(sizeof(T) * nz);
          pCol = (size_t*)malloc(sizeof(size_t) * nz);
      }
      else if (nz == 0) {
          pVal = NULL;
          pCol = NULL;
      }
      pRow[0] = 0;
      int k = 0;
      i = 0;
      for (i; i < sz; i++) {
          int j = 0;
          for (j; j < sz; j++) {
              if (arr[i][j] != 0) {
                  pVal[k] = arr[i][j];
                  pCol[k] = j;
                  k++;
              }
          }
          pRow[i + 1] = k;
      }
  }
  TDynamicMatrix(const TDynamicMatrix& m) { // к-ор копирования
      sz = m.sz;
      nz = m.nz;
      pRow = (size_t*)malloc(sizeof(size_t) * (sz + 1));
      memcpy(pRow, m.pRow, (sz + 1) * sizeof(size_t));
      if (nz == 0) {
          pVal = NULL;
          pCol = NULL;
      }
      if (nz > 0) {
          pVal = (T*)malloc(sizeof(T) * nz);
          pCol = (size_t*)malloc(sizeof(size_t) * nz);
          memcpy(pVal, m.pVal, nz * sizeof(T));
          memcpy(pCol, m.pCol, nz * sizeof(size_t));
      }
  }
  TDynamicMatrix(TDynamicMatrix&& m) noexcept { // к-ор перемещения
      sz = m.sz;
      nz = m.nz;
      pVal = m.pVal;
      pCol = m.pCol;
      pRow = m.pRow;
      m.pVal = NULL;
      m.pCol = NULL;
      m.pRow = NULL;
      m.sz = 0;
      m.nz = 0;
  }
  ~TDynamicMatrix() {
      free(pVal);
      free(pCol);
      free(pRow);
  }

  // присваивание
  TDynamicMatrix& operator=(const TDynamicMatrix& m) {
      if (this == &m) {
          return *this;
      }
      sz = m.sz;
      nz = m.nz;
      free(pRow);
      free(pVal);
      free(pCol);
      pRow = (size_t*)malloc(sizeof(size_t) * (sz + 1));
      memcpy(pRow, m.pRow, (sz + 1) * sizeof(size_t));
      if (nz == 0) {
          pVal = NULL;
          pCol = NULL;
      }
      if (nz > 0) {
          pVal = (T*)malloc(sizeof(T) * nz);
          pCol = (size_t*)malloc(sizeof(size_t) * nz);
          memcpy(pVal, m.pVal, nz * sizeof(T));
          memcpy(pCol, m.pCol, nz * sizeof(size_t));
      }
      return *this;
  }
  TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept {
      if (this == &m) {
          return *this;
      }
      free(pVal);
      free(pRow);
      free(pCol);
      sz = m.sz;
      nz = m.nz;
      pVal = m.pVal;
      pCol = m.pCol;
      pRow = m.pRow;
      m.pVal = NULL;
      m.pCol = NULL;
      m.pRow = NULL;
      m.sz = 0;
      m.nz = 0;
      return *this;
  }

  size_t size() const noexcept {
      return sz;
  }
  T at(size_t i, size_t j) const {
      if (i >= sz || j >= sz) {
          throw out_of_range("...");
      }
      int k = pRow[i];
      for (k; k < pRow[i+1]; k++) {
          if (pCol[k] == j) {
              return pVal[k];
          }
      }
      return 0;
  }

  struct RowProxy {
      TDynamicMatrix* mat;
      int row;
      T& operator[](int col) {
          int k = mat->pRow[row];
          for (k; k < mat->pRow[row + 1]; k++) {
              if (mat->pCol[k] == col) {
                  return mat->pVal[k];
              }
              if (mat->pCol[k] > col) {
                  break;
              }
          }
          mat->nz++;
          mat->pVal = (T*)realloc(mat->pVal, sizeof(T) * mat->nz);
          mat->pCol = (size_t*)realloc(mat->pCol, sizeof(size_t) * mat->nz);
          int idx = mat->nz - 1;
          for (idx; idx > k; idx--) {
              mat->pVal[idx] = mat->pVal[idx - 1];
              mat->pCol[idx] = mat->pCol[idx - 1];
          }
          mat->pVal[k] = 0;
          mat->pCol[k] = col;
          int r = row + 1;
          for (r; r <= mat->sz; r++) {
              mat->pRow[r]++;
          }
          return mat->pVal[k];
      }
  };

  struct ConstRowProxy {
      const TDynamicMatrix* mat;
      int row;

      T operator[](int col) const {
          return mat->at(row, col);
      }
  };

  RowProxy operator[](int i) {
      return RowProxy{ this, i };
  }

  ConstRowProxy operator[](int i) const {
      return ConstRowProxy{ this, i };
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept{
      if (sz != m.sz || nz != m.nz) {
          return false;
      }
      int i = 0;
      for (i; i < (sz + 1); i++) {
          if (pRow[i] != m.pRow[i]) {
              return false;
          }
      }
      i = 0;
      for (i; i < nz; i++) {
          if (pVal[i] != m.pVal[i] || pCol[i] != m.pCol[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept {
      
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val){
      if (val == 0 || nz == 0) {
          return TDynamicMatrix(sz);
      }
      TDynamicMatrix res(*this);
      int i = 0;
      for (i; i < res.nz; i++) {
          res.pVal[i] *= val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v){
      if (sz != v.size()) {
          throw out_of_range("Razmeri ne sovpadayut");
      }
      T* tmp = (T*)malloc(sizeof(T) * sz);
      int i = 0;
      for (i; i < sz; i++) {
          T sum = 0;
          int k = pRow[i];
          for (k; k < pRow[i + 1]; k++) {
              sum += pVal[k] * v[pCol[k]];
          }
          tmp[i] = sum;
      }
      TDynamicVector<T> res(tmp, sz);
      free(tmp);
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const{
      if (sz != m.sz) {
          throw out_of_range("Razmeri matric ne sovpadayut");
      }
      TDynamicMatrix res(sz);
      T* tmpVal = (T*)malloc(sizeof(T) * (nz + m.nz));
      size_t* tmpCol = (size_t*)malloc(sizeof(size_t) * (nz + m.nz));
      res.pRow[0] = 0;
      int k = 0;
      int r = 0;
      for (r; r < sz; r++) {
          int i = pRow[r], j = m.pRow[r];
          while (i < pRow[r + 1] && j < m.pRow[r + 1]) {
              if (pCol[i] < m.pCol[j]) {
                  tmpCol[k] = pCol[i];
                  tmpVal[k] = pVal[i];
                  k++;
                  i++;
              }
              else if (pCol[i] > m.pCol[j]) {
                  tmpCol[k] = m.pCol[j];
                  tmpVal[k] = m.pVal[j];
                  k++;
                  j++;
              }
              else if (pCol[i] == m.pCol[j]) {
                  T sum = pVal[i] + m.pVal[j];
                  if (sum != 0) {
                      tmpCol[k] = pCol[i];
                      tmpVal[k] = sum;
                      k++;
                  }
                  i++;
                  j++;
              }
          }
          while (i < pRow[r+1]) {
              tmpCol[k] = pCol[i];
              tmpVal[k] = pVal[i];
              i++;
              k++;
          }
          while (j < m.pRow[r+1]) {
              tmpCol[k] = m.pCol[j];
              tmpVal[k] = m.pVal[j];
              j++;
              k++;
          }
          res.pRow[r + 1] = k;
      }
      if (k > 0) {
          res.nz = k;
          res.pCol = (size_t*)realloc(tmpCol, sizeof(size_t) * k);
          res.pVal = (T*)realloc(tmpVal, sizeof(T) * k);
      }
      else {
          free(tmpCol);
          free(tmpVal);
      }
      return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) const{
      if (sz != m.sz) {
          throw out_of_range("Razmeri matric ne sovpadayut");
      }
      TDynamicMatrix res(sz);
      T* tmpVal = (T*)malloc(sizeof(T) * (nz + m.nz));
      size_t* tmpCol = (size_t*)malloc(sizeof(size_t) * (nz + m.nz));
      res.pRow[0] = 0;
      int k = 0;
      int r = 0;
      for (r; r < sz; r++) {
          int i = pRow[r], j = m.pRow[r];
          while (i < pRow[r + 1] && j < m.pRow[r + 1]) {
              if (pCol[i] < m.pCol[j]) {
                  tmpCol[k] = pCol[i];
                  tmpVal[k] = pVal[i];
                  k++;
                  i++;
              }
              else if (pCol[i] > m.pCol[j]) {
                  tmpCol[k] = m.pCol[j];
                  tmpVal[k] = -m.pVal[j];
                  k++;
                  j++;
              }
              else if (pCol[i] == m.pCol[j]) {
                  T diff = pVal[i] - m.pVal[j];
                  if (diff != 0) {
                      tmpCol[k] = pCol[i];
                      tmpVal[k] = diff;
                      k++;
                  }
                  i++;
                  j++;
              }
          }
          while (i < pRow[r + 1]) {
              tmpCol[k] = pCol[i];
              tmpVal[k] = pVal[i];
              i++;
              k++;
          }
          while (j < m.pRow[r + 1]) {
              tmpCol[k] = m.pCol[j];
              tmpVal[k] = -m.pVal[j];
              j++;
              k++;
          }
          res.pRow[r + 1] = k;
      }
      if (k > 0) {
          res.nz = k;
          res.pCol = (size_t*)realloc(tmpCol, sizeof(size_t) * k);
          res.pVal = (T*)realloc(tmpVal, sizeof(T) * k);
      }
      else {
          free(tmpCol);
          free(tmpVal);
      }
      return res;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) const{
      if (sz != m.sz) {
          throw out_of_range("Razmeri matric ne sovpadayut");
      }
      TDynamicMatrix res(sz);
      res.pRow[0] = 0;
      if (nz == 0 || m.nz == 0) {
          return res;
      }
      T* rowBuf = (T*)malloc(sizeof(T) * sz);
      int r = 0;
      for (r; r < sz; r++) {
          memset(rowBuf, 0, sizeof(T) * sz);
          int i = pRow[r];
          for (i; i < pRow[r + 1]; i++) {
              int colA = pCol[i];
              T valA = pVal[i];
              int j = m.pRow[colA];
              for (j; j < m.pRow[colA + 1]; j++) {
                  rowBuf[m.pCol[j]] += valA * m.pVal[j];
              }
          }
          int c = 0;
          for (c; c < sz; c++) {
              if (rowBuf[c] != 0) {
                  res.pCol = (size_t*)realloc(res.pCol, sizeof(size_t) * (res.nz + 1));
                  res.pVal = (T*)realloc(res.pVal, sizeof(T) * (res.nz + 1));
                  res.pCol[res.nz] = c;
                  res.pVal[res.nz] = rowBuf[c];
                  res.nz++;
              }
          }
          res.pRow[r + 1] = res.nz;
      }
      free(rowBuf);
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m){
      T** tmp = (T**)malloc(sizeof(T*) * m.sz);
      int i = 0;
      for (i; i < m.sz; i++) {
          tmp[i] = (T*)malloc(sizeof(T) * m.sz);
          int j = 0;
          for (j; j < m.sz; j++) {
              istr >> tmp[i][j];
          }
      }
      m = TDynamicMatrix(tmp, m.sz);
      i = 0;
      for (i; i < m.sz; i++) {
          free(tmp[i]);
      }
      free(tmp);
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m){
      int i = 0;
      for (i; i < m.sz; i++) {
          int k = m.pRow[i],j = 0;
          for (j; j < m.sz; j++) {
              if (k < m.pRow[i + 1] && m.pCol[k] == j) {
                  ostr << m.pVal[k] << ' ';
                  k++;
              }
              else {
                  ostr << 0 << ' ';
              }
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif