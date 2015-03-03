
#include <iostream>
#include <vector>

class binary_heap
{ private:
    int n_items;
    vector <int> heap;
    void order_up(int);
    void order_down(int);
    void swap(int, int);
    int max(int, int);
  public:
      binary_heap();
      ~binary_heap() { }
    int get_apex();
    int pop();
    void add_to_heap(int);
    int get_size();
    int get_number_of_items();
    void print();
};

binary_heap::binary_heap()
{ heap.resize(100);
  // heap.at(0) not considered part of structure
  //             1
  //          2     3
  //         4 5   6 7
  // n_items = index of next element to be added
  n_items = 1; }

void binary_heap::add_to_heap(int a)
{ int size = heap.size();
  if (n_items == size - 1)
    heap.resize(2 * size);
  heap.at(n_items) = a;
  order_up(n_items);
  n_items += 1; }

void binary_heap::order_up(int index)
{ if (index <= 1)
    return;
  int parent = index >> 1;
  if (heap.at(index) > heap.at(parent))
  { swap(index, parent);
    order_up(parent); } }

int binary_heap::get_apex()
{ return heap.at(1); }

int binary_heap::pop()
{ if (n_items == 1)
    return -1;
  int apex = heap.at(1);
  n_items -= 1;
  heap.at(1) = heap.at(n_items);
  order_down(1);
  return apex; }

void binary_heap::order_down(int index)
{ int child_one = index * 2;
  int child_two = index * 2 + 1;
  if (child_one >= n_items)
    return;
  int max_child = max(child_one, child_two);
  if (heap.at(max_child) > heap.at(index))
  { swap(index, max_child);
    order_down(max_child); } }

int binary_heap::get_size()
{ return heap.size(); }

int binary_heap::get_number_of_items()
{ return n_items-1; }

void binary_heap::print()
{ cout << "heap contents:\n";
  for (int i = 1; i < n_items; i += 1)
    cout << heap.at(i) << " ";
  cout << "\n\n"; }

int binary_heap::max(int child_one, int child_two)
{ if (child_one >= n_items || child_two > n_items)
  { cout << "error in max";
    exit(1); }
  if (child_two == n_items)
    return child_one;
  if (heap.at(child_one) > heap.at(child_two))
    return child_one;
  return child_two; }

void binary_heap::swap(int index_one, int index_two)
{ int temp = heap.at(index_one);
  heap.at(index_one) = heap.at(index_two);
  heap.at(index_two) = temp; }

void test_run(int N)
{ binary_heap X;
  for (int i = 0; i < N; i +=1 )
    X.add_to_heap(random()%1000);
  cout << "max: " << X.get_apex() << "\n\n";
  X.print();
  while (X.get_number_of_items())
    cout << X.pop() << "\n"; }

int main()
{ test_run(20); }
