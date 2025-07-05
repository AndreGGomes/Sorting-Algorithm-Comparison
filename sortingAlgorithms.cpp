#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


void bubbleSort(vector<int>& v, long long& swaps, long long& comparisons)
{
    int n = v.size();
    for (int i = 0; i < n-1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n-i-1; j++)
        {
            comparisons++;
            if (v[j] > v[j+1])
            {
                swap(v[j], v[j+1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}


void insertionSort(vector<int>& v, long long& swaps, long long& comparisons)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j > 0)
        {
            comparisons++;
            if (v[j-1] > v[j])
            {
                swap(v[j], v[j-1]);
                swaps++;
                j--;
            }
            else break;
        }
    }
}

void selectionSort(vector<int>& v, long long& swaps, long long& comparisons)
{
    int n = v.size();
    for (int i = 0; i < n-1; i++)
    {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
        {
            comparisons++;
            if (v[j] < v[min_idx])
                min_idx = j;
        }
        if (i != min_idx)
        {
            swap(v[i], v[min_idx]);
            swaps++;
        }
    }
}

void merge(vector<int>& v, int left, int mid, int right, long long& comparisons)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> tempLeft(n1);
    vector<int> tempRight(n2);
    for (int i = 0; i < n1; i++)
        tempLeft[i] = v[left + i];
    for (int j = 0; j < n2; j++)
        tempRight[j] = v[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        comparisons++;
        if (tempLeft[i] <= tempRight[j])
        {
            v[k] = tempLeft[i];
            i++;
        }
        else
        {
            v[k] = tempRight[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = tempLeft[i];
        i++; k++;
    }
    while (j < n2)
    {
        v[k] = tempRight[j];
        j++; k++;
    }
}

void mergeSort(vector<int>& v, int left, int right, long long& swaps, long long& comparisons)
{
    swaps = 0; //não são feitos swaps na mergeSort
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(v, left, mid, swaps, comparisons);
    mergeSort(v, mid + 1, right, swaps, comparisons);
    merge(v, left, mid, right, comparisons);
}

void mergeSortWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    mergeSort(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortMiddle(vector<int>& v, int left, int right, long long& swaps, long long& comparisons)
{
    if (left >= right) return;
    int pivot = v[(left + right) / 2];
    int i = left, j = right;
    while (i <= j)
    {
        while (true) { comparisons++; if (!(v[i] < pivot)) break; i++; }
        while (true) { comparisons++; if (!(v[j] > pivot)) break; j--; }
        if (i <= j)
        {
            if (i != j)
            {
                swap(v[i], v[j]);
                swaps++;
            }
            i++; j--;
        }
    }
    quickSortMiddle(v, left, j, swaps, comparisons);
    quickSortMiddle(v, i, right, swaps, comparisons);
}

void quickSortMiddleWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    quickSortMiddle(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortLeft(vector<int>& v, int left, int right, long long& swaps, long long& comparisons)
{
    if (left >= right) return;
    int pivot = v[left];
    int i = left, j = right;
    while (i <= j)
    {
        while (true) { comparisons++; if (!(v[i] < pivot)) break; i++; }
        while (true) { comparisons++; if (!(v[j] > pivot)) break; j--; }
        if (i <= j)
        {
            if (i != j)
            {
                swap(v[i], v[j]);
                swaps++;
            }
            i++; j--;
        }
    }
    quickSortLeft(v, left, j, swaps, comparisons);
    quickSortLeft(v, i, right, swaps, comparisons);
}

void quickSortLeftWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    quickSortLeft(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortRight(vector<int>& v, int left, int right, long long& swaps, long long& comparisons)
{
    if (left >= right) return;
    int pivot = v[right];
    int i = left, j = right;
    while (i <= j)
    {
        while (true) { comparisons++; if (!(v[i] < pivot)) break; i++; }
        while (true) { comparisons++; if (!(v[j] > pivot)) break; j--; }
        if (i <= j)
        {
            if (i != j)
            {
                swap(v[i], v[j]);
                swaps++;
            }
            i++; j--;
        }
    }
    quickSortRight(v, left, j, swaps, comparisons);
    quickSortRight(v, i, right, swaps, comparisons);
}

void quickSortRightWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    quickSortRight(v, 0, v.size() - 1, swaps, comparisons);
}

void bestQuickSort(vector<int>& v, long long& swaps, long long& comparisons, int low = 0, int high = -1)
{
    if (high == -1) high = v.size() - 1;
    if (high - low < 16)
    {
        for (int i = low + 1; i <= high; i++)
        {
            int j = i;
            while (j > low)
            {
                comparisons++;
                if (v[j-1] > v[j])
                {
                    swap(v[j], v[j-1]);
                    swaps++;
                    j--;
                }
                else break;
            }
        }
        return;
    }
    int mid = low + (high - low) / 2;
    comparisons++; if (v[mid] < v[low]) { swap(v[low], v[mid]); swaps++; }
    comparisons++; if (v[high] < v[low]) { swap(v[low], v[high]); swaps++; }
    comparisons++; if (v[mid] < v[high]) { swap(v[mid], v[high]); swaps++; }
    int pivot = v[high];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do { i++; comparisons++; } while (v[i] < pivot);
        do { j--; comparisons++; } while (v[j] > pivot);
        if (i >= j) break;
        swap(v[i], v[j]);
        swaps++;
    }
    bestQuickSort(v, swaps, comparisons, low, j);
    bestQuickSort(v, swaps, comparisons, j + 1, high);
}

void bestQuickSortWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    bestQuickSort(v, swaps, comparisons);
}

void sortWrapper(vector<int>& v, long long& swaps, long long& comparisons)
{
    swaps = 0;
    comparisons = 0;
    sort(v.begin(), v.end());
}