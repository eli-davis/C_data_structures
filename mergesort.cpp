#include <iostream>
#include <ctime>
#include <cstdlib>

void swap(int * A, int index_one, int index_two)
{
    int temp = A[index_one];
    A[index_one] = A[index_two];
    A[index_two] = temp;
}

void merge(int * A, int * A_copy, const int low_index, const int mid_index, const int high_index)
{
    int ii_low = low_index;
    int ii_high = mid_index + 1; 

    for (int ii = low_index; ii <= high_index; ii += 1)
    {
	if (ii_low > mid_index)
        {
            A_copy[ii] = A[ii_high];
            ii_high += 1;
        }
        else if (ii_high > high_index)
        {
            A_copy[ii] = A[ii_low];
            ii_low += 1;
        }
        else
        {
            if (A[ii_low] < A[ii_high])
            {
                A_copy[ii] = A[ii_low];
                ii_low += 1;
            }
            else
            {
                A_copy[ii] = A[ii_high];
                ii_high += 1;
            }
        }
    }

    for (int ii = low_index; ii <= high_index; ii += 1)
    {
        A[ii] = A_copy[ii];
    }
}

void mergesort(int * A, int * A_copy, int low_index, int high_index)
{
    int mid_index = (low_index + high_index) / 2;

    if (high_index - low_index >= 2)
    {
        mergesort(A, A_copy, low_index, mid_index);
        mergesort(A, A_copy, mid_index + 1, high_index);
        merge(A, A_copy, low_index, mid_index, high_index);
    }
    else if (high_index - low_index == 1)
    {
	if (A[low_index] > A[high_index])
        {
            swap(A, low_index, high_index);
        }
    }
}


void mergesort(int * A, int n_items)
{
    int * A_copy = new int[n_items];
    mergesort(A, A_copy, 0, n_items - 1);
    delete [] A_copy;
    A_copy = NULL;
}


void test_one(int n_items)
{
    srand(time(NULL));
    int * A = new int[n_items];
    for (int ii = 0; ii < n_items; ii += 1)
    {
	A[ii] = rand() % 2;
    }
    
    for (int ii = 0; ii < n_items; ii += 1)
    {
	cout << A[ii] << " ";
    }
    cout << "\n\n";

    mergesort(A, n_items);

    for (int ii = 0; ii < n_items; ii += 1)
    {
	cout << A[ii] << " ";
    }
    cout << "\n\n";

    delete [] A;
    A = NULL;
}


void main()
{
    test_one(20);
}
