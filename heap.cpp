#include <cmath>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

// standard heap, starts at index 1
//             1
//          2     3
//         4 5   6 7
// n_items = index of next element to be added

// min heap if (*compare)(int, int) == return_min
// max heap if (*compare)(int, int) == return_max

int return_min(int a, int b)
{
    if (a < b) 
    {
        return a;
    }
    return b;
}

int return_max(int a, int b)
{
    if (a > b) 
    {
        return a;
    }
    return b;
}

using namespace std;

class binary_heap { 
    int n_items;
    vector <int> heap;
    void order_up(int index);
    void order_down(int index);
    void swap(int index_one, int index_two);
    int (*compare)(int, int);
public:
    binary_heap(bool is_min_heap = true);
    binary_heap(int size, bool is_min_heap = true);
    ~binary_heap();
    int pop();
    void add(int);
    int number_of_items();
    void print();
};

/*
 * is_min_heap defaults to true
 */
binary_heap::binary_heap(bool is_min_heap)
{ 
    heap.resize(100);
    if (is_min_heap)
    {
        compare = return_min;
    }
    else
    {
        compare = return_max;
    }
    n_items = 0; 
}

/*
 * is_min_heap defaults to true
 */
binary_heap::binary_heap(int size, bool is_min_heap)
{ 
    heap.resize(size); 
    if (is_min_heap)
    {
        compare = return_min;
    }
    else
    {
        compare = return_max;
    }
    n_items = 0; 
}

binary_heap::~binary_heap()
{
    heap.clear();
}

void binary_heap::add(int a)
{ 
    int size = heap.size();
    if (n_items == size - 1)
    {
        heap.resize(2 * size);
    }
    n_items += 1;
    heap.at(n_items) = a;
    order_up(n_items);
}

void binary_heap::order_up(int index)
{ 
    if (index <= 1) 
    {
        return;
    }
    int parent = index >> 1;
    if ( compare(heap.at(index), heap.at(parent)) == heap.at(index) )
    {
        swap(index, parent);
        order_up(parent); 
    } 
}

int binary_heap::pop()
{ 
    if (n_items == 0)
    {
        return -1;
    }
    int apex = heap.at(1);
    heap.at(1) = heap.at(n_items);
    n_items -= 1;
    order_down(1);
    return apex; 
}

void binary_heap::order_down(int index)
{ 
    int child_one = index * 2;
    int child_two = index * 2 + 1;
    int child;
    if (child_one > n_items)
    {
        return;
    }
    else if (child_one == n_items) 
    {
        child = child_one;
    }
    else if ( compare(heap.at(child_one), heap.at(child_two)) == heap.at(child_one) )
    {
        child = child_one;
    }
    else
    {
        child = child_two;
    }

    if ( compare(heap.at(child), heap.at(index)) == heap.at(child) )
    { 
        swap(index, child);
        order_down(child); 
    } 
}

int binary_heap::number_of_items()
{ 
    return n_items; 
}

void binary_heap::print()
{ 
    cout << "heap contents:\n";
    int ii = 1;
    int level = 1;
    while (ii <= n_items) 
    {
        cout << heap.at(ii) << " ";
        ii += 1;
        if (pow(2, level) == ii) 
        {
            level += 1;
            cout << "\n";
        }
    }
    cout << "\n\n";
}

void binary_heap::swap(int index_one, int index_two)
{ 
    int temp = heap.at(index_one);
    heap.at(index_one) = heap.at(index_two);
    heap.at(index_two) = temp; 
}

void test_one(int N)
{
    binary_heap X;
    srand(time(NULL));
    for (int i = 0; i < N; i += 1 )
    { 
        X.add(rand() % 1000);
    }
    X.print();
    while (X.number_of_items() > 0)
    {
        cout << X.pop() << "\n";
    }
}

int main()
{ 
    test_one(20); 
}
