#include <iostream>
#include <sys/time.h>
#include <sys/resource.h>

const int N = 100000;

double getcputime(void)
{ struct timeval tim;
  struct rusage ru;
  getrusage(RUSAGE_SELF, &ru);
  tim=ru.ru_utime;
  double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  tim=ru.ru_stime;
  t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
  return t; }

int get_pivot_pos(int * X, int index_one, int index_two)
{ int a = X[index_one];
  int b = X[index_two >> 1];
  int c = X[index_two];
  //median
  if ((b - a) * (a - c) >= 1)
    return index_one;
  if ((a - b) * (b - c) >= 1)
    return index_two >> 1;
  return index_two; }

inline void swap(int & a, int & b)
{ int temp = a;
  a = b;
  b = temp; }

inline void selection_sort(int * X, int index_one, int index_two)
{ int min_pos = 0;
  for (int i = index_one; i < index_two; i += 1)
  { min_pos = i;
    for (int j = i + 1; j <= index_two; j += 1)
      if (X[j] < X[min_pos])
        min_pos = j;
    if (i != min_pos)
      swap(X[i], X[min_pos]); } }

void quicksort(int * X, int index_one, int index_two)
{ int difference = index_two - index_one;
  if (difference == 0)
    return;
  else if (difference == 1)
  { if (X[index_one] > X[index_two])
      swap(X[index_one], X[index_two]); }
  else if (difference <= 6 )
    selection_sort(X, index_one, index_two);
  else
  { int pivot_pos = get_pivot_pos(X, index_one, index_two);
    int pivot = X[pivot_pos];
    int P = index_one, Q = index_two;
    while (true)
    { while (P < index_two && X[P] <= pivot)
        P += 1;
      while (Q > index_one && X[Q] >= pivot)
        Q -= 1;
      if (P < Q)
      { swap(X[P], X[Q]);
        P += 1;
        Q -= 1; }
      else
      { if (P <= pivot_pos && P < index_two)
        { swap(X[P], X[pivot_pos]);
          P += 1; }
        else if (Q >= pivot_pos && Q > index_one)
        { swap(X[Q], X[pivot_pos]);
          Q -= 1; }
        break; } }
    quicksort(X, index_one, Q);
    quicksort(X, P, index_two); } }

void print(int * X, int size)
{ for (int i = 0; i < size; i += 1)
  { if (i % 10 == 0) cout << "\n";
    cout << X[i] << " "; }
 cout << "\n\n"; }

bool is_sorted(int * X, int size)
{ for (int i = 1; i < size; i += 1)
    if (X[i-1] > X[i])
      return false;
  return true; }

void my_sort()
{ int X[N];
  for (int i = 0; i < N; i += 1)
    X[i] = random() % 10000;
  double begin_time = getcputime();
  quicksort(X, 0, N-1);
  double end_time = getcputime();
  double t = end_time - begin_time;
  if (is_sorted(X, N))
    cout << "\nProgram sorted " << N << " items in " << t << " seconds.\n";
  else
    cout << "\nError - data NOT sorted";  }

void lib_sort()
{ int X[N];
  for (int i = 0; i < N; i += 1)
    X[i] = random() % 10000;
  double begin_time = getcputime();
  sort(X, X + N);
  double end_time = getcputime();
  double t = end_time - begin_time;
  if (is_sorted(X, N))
    cout << "\nSTL sorted " << N << " items in " << t << " seconds.\n";
  else
    cout << "\nError - data NOT sorted";  }

int main()
{ srandom(613);
  my_sort();
  lib_sort();  }
