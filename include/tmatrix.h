// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:  
  size_t size() const noexcept { return sz; }

  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz <= 0 || sz > MAX_VECTOR_SIZE) 
      throw out_of_range("Vector size should be greater than zero and less than max");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      if (sz != v.sz) {
          T* p = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem); return *this;

      /* Или версия со свапом, с лекции

      if (this == &v) return *this;
      TDynamicVector tmp(v);
      swap(*this, tmp);
      return *this;

      */
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }



  // индексация
  T& operator[](size_t ind) 
  {
      return pMem[ind];            // UB если ind >= sz, но тут вроде не нужен контроль
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind]; // хз зачем нам конст и не конст но они одинаковые
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind <= 0) throw std::out_of_range("TDynamicVector at() index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind <= 0) throw std::out_of_range("TDynamicVector at() const index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return true; // одинаковые указатели
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; ++i)
          if (!(pMem[i] == v.pMem[i])) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return false; // одинаковые указатели
      if (sz != v.sz) return true;
      for (size_t i = 0; i < sz; ++i)
          if (pMem[i] == v.pMem[i]) return false;
      return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz); 
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] + val; 
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector operator+ size isnt right");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector operator- size isnt right");
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector operator* size isnt right");
      // возвращаться нам будет чиселко ( ну тип Т ), будем пользоваться стандартным скалярным произв a*b =a1*b1 + a2*b2....
      T res = T();
      for (size_t i = 0; i < sz; i++)
          res = res + (pMem[i] * v.pMem[i]);

      return res;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem; // поскольку прайват потомок?
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) // то есть создается вектор из векторов s*s, но из-за этого надо строчки пересоздавать
  {
      if (s == 0 || s > MAX_MATRIX_SIZE) throw out_of_range("Matrix size must be >0 and less than max");

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];




  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      // то есть просто отправляем операцию в вектор
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz); 
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] * val; 
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != sz) throw invalid_argument("TDynamicMatrix operator* vector size isnt right");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; ++i)
          res[i] = pMem[i] * v;
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.size() != sz) throw invalid_argument("TDynamicMatrix operator+ mat size isnt right");
      TDynamicMatrix tmp(sz); 
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] + m.pMem[i]; 
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.size() != sz) throw invalid_argument("TDynamicMatrix operator- mat size isnt right");
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] - m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (m.size() != sz) throw invalid_argument("TDynamicMatrix operator* mat size isnt right");
      TDynamicMatrix tmp(sz); 
      for (size_t i = 0; i < sz; i++) 
          for (size_t j = 0; j < sz; j++) 
              for (size_t k = 0; k < sz; k++) tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j]; 
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          for (size_t j = 0; j < v.sz; j++)
              istr >> v.pMem[i][j]; // нужн operator>> для T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << v.pMem[i][j];
              if (j + 1 < v.sz) ostr << ' ';
          }
          if (i + 1 < v.sz) ostr << '\n';
      }
      return ostr;
  }
  // пришлось добавить, т.к. без этого не работало - ругался что метод недоступен хотя он паблик... даже юзинг не помогал
  size_t size() const noexcept { return sz; }

};

#endif
