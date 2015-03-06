#include <iostream>
#include <cmath>

template<typename T>
class Vector
{ protected:
    int size;
    T * A;
  public:
      Vector();
      Vector(int sz);
      ~Vector();
    int length();
    T get(int pos);
    void set(int pos, T);
    void resize(int new_size);
    void print();
};

template<typename T> Vector<T>::Vector()
{ size = 100;
  A = new T[size];
  for (int i = 0; i < size; i += 1)
    A[i] = 0; }

template<typename T> Vector<T>::Vector(int sz)
{ size = sz;
  A = new T[size];
  for (int i = 0; i < size; i += 1)
    A[i] = 0; }

template<typename T> Vector<T>::~Vector()
{ delete [] A; }

template<typename T> int Vector<T>::length()
{ return size; }

template<typename T> T Vector<T>::get(int pos)
{ if (pos < 0 || pos >= size)
  { cerr << "out of bounds Vector read\n";
    exit(1); }
  return A[pos]; }

template<typename T> void Vector<T>::set(int pos, T value)
{ if (pos < 0 || pos > size)
  { cerr << "out of bounds Vector write\n";
    exit(1);  }
  if (pos == size)
    resize(2 * size);
  A[pos] = value; }


template<typename T> void Vector<T>::set(int pos, T value)
{ if (pos < 0 || pos > size)
  { cerr << "out of bounds Vector write\n";
    exit(1);  }
  if (pos == size)
    resize(2 * size);
  A[pos] = value; }

template<typename T> void Vector<T>::resize(int new_size)
{ int old_size = size;
  T * old_A = A;
  size = new_size;
  A = new T[size];
  for (int i = 0; i < old_size; i += 1)
    A[i] = old_A[i];
  for (int i = old_size; i < size; i += 1)
    A[i] = 0;
  delete [] old_A; }

template<typename T> void Vector<T>::print()
{ for (int i = 0; i < size; i += 1)
  { if (i % 10 == 0)
      cout << endl;
    cout << A[i] << " "; } }

int test1()
{ Vector<int> A(13);
  A.set(12, 15);
  A.set(13, 15);
  A.resize(17);
  A.print();
  cout << endl << A.get(16);  }

int main()
{ test1(); }
