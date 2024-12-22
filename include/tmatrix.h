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
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  // Оператор присваивания (копирования)
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this; // Самоприсваивание

      T* newMem = new T[v.sz];
      std::copy(v.pMem, v.pMem + v.sz, newMem);

      delete[] pMem;
      pMem = newMem;
      sz = v.sz;

      return *this;
  }

  // Оператор присваивания (перемещения)
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this; // Самоприсваивание

      delete[] pMem;

      sz = v.sz;
      pMem = v.pMem;

      v.sz = 0;
      v.pMem = nullptr;

      return *this;
  }

  // Индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // Индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // Сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; ++i)
      {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // Скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }

  TDynamicVector operator-(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }

  TDynamicVector operator*(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // Векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Vector sizes do not match");

      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Vector sizes do not match");

      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; ++i)
      {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw out_of_range("Vector sizes do not match");

      T result = T();
      for (size_t i = 0; i < sz; ++i)
      {
          result += pMem[i] * v.pMem[i];
      }
      return result;
  };


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
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;

public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // Сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i)
        {
            if (pMem[i] != m.pMem[i]) return false;
        }
        return true;
    }

    // Матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            result.pMem[i] = pMem[i] * val;
        }
        return result;
    }

    // Матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw out_of_range("Matrix and vector sizes do not match");

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            result[i] = pMem[i] * v;
        }
        return result;
    }

    // Матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("Matrix sizes do not match");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            result.pMem[i] = pMem[i] + m.pMem[i];
        }
        return result;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("Matrix sizes do not match");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            result.pMem[i] = pMem[i] - m.pMem[i];
        }
        return result;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw out_of_range("Matrix sizes do not match");

        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
        {
            for (size_t j = 0; j < sz; ++j)
            {
                result[i][j] = T();
                for (size_t k = 0; k < sz; ++k)
                {
                    result[i][j] += (*this)[i][k] * m[k][j];
                }
            }
        }
        return result;
    }

    // Ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; ++i)
        {
            istr >> m.pMem[i];
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; ++i)
        {
            ostr << m.pMem[i] << std::endl;
        }
        return ostr;
    }
};

#endif
