#include <vector>
using namespace std;

void bubbleSort(vector<int>& v, int& swaps)
{
    int n = v.size();
    for (int i = 0; i < n-1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n-i-1; j++)
        {
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

void insertionSort(vector<int>& v, int& swaps)
{
    int n = v.size();
    for (int i = 1; i < n; i++)
    {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            swaps++;
            j--;
        }
        v[j + 1] = key;
    }
}

void selectionSort(vector<int>& v, int& swaps)
{
    int n = v.size();
    for (int i = 0; i < n-1; i++)
    {
        int low_index = i;
        for (int j = i+1; j < n; j++)
        {
            if (v[j] < v[low_index])
            {
                low_index = j;
            }
        }
        if (i != low_index) {
            swap(v[i], v[low_index]);
            swaps++;
        }
    }
}

void merge(vector<int>& v, int left, int mid, int right, int& swaps)
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
        swaps++; // Cada atribuição é considerada uma "troca" para merge sort
        k++;
    }
    while (i < n1)
    {
        v[k] = tempLeft[i];
        i++; k++; swaps++;
    }
    while (j < n2)
    {
        v[k] = tempRight[j];
        j++; k++; swaps++;
    }
}

void mergeSort(vector<int>& v, int left, int right, int& swaps)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(v, left, mid, swaps);
    mergeSort(v, mid + 1, right, swaps);
    merge(v, left, mid, right, swaps);
}

void mergeSortWrapper(vector<int>& v, int& swaps)
{
    mergeSort(v, 0, v.size() - 1, swaps);
}

void quickSortMiddle(vector<int>& v, int left, int right, int& swaps)
{
    if (left >= right) return;
    int pivot = v[(left + right) / 2];
    int i = left, j = right;
    while (i <= j)
    {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) 
        {
            if (i != j)
            { 
                swap(v[i], v[j]);
                swaps++;
            }
            i++;
            j--;
        }
    }
    quickSortMiddle(v, left, j, swaps);
    quickSortMiddle(v, i, right, swaps);
}

void quickSortMiddleWrapper(vector<int>& v, int& swaps)
{
    quickSortMiddle(v, 0, v.size() - 1, swaps);
}

void quickSortLeft(vector<int>& v, int left, int right, int& swaps)
{
    if (left >= right) return;
    int pivot = v[left];
    int i = left, j = right;
    while (i <= j)
    {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) 
        {
            if (i != j)
            {
                swap(v[i], v[j]);
                swaps++;
            }
            i++;
            j--;
        }
    }
    quickSortLeft(v, left, j, swaps);
    quickSortLeft(v, i, right, swaps);
}

void quickSortLeftWrapper(vector<int>& v, int& swaps)
{
    quickSortLeft(v, 0, v.size() - 1, swaps);
}

void quickSortRight(vector<int>& v, int left, int right, int& swaps)
{
    if (left >= right) return;
    int pivot = v[right];
    int i = left, j = right;
    while (i <= j)
    {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) 
        {
            if (i != j) { swap(v[i], v[j]); swaps++; }
            i++; j--;
        }
    }
    quickSortRight(v, left, j, swaps);
    quickSortRight(v, i, right, swaps);
}

void quickSortRightWrapper(vector<int>& v, int& swaps)
{
    quickSortRight(v, 0, v.size() - 1, swaps);
}

void bestQuickSort(vector<int>& v, int& swaps, int low = 0, int high = -1)
{
    if (high == -1) high = v.size() - 1;
    if (high - low < 16)
    {
        for (int i = low + 1; i <= high; i++)
        {
            int key = v[i];
            int j = i - 1;
            while (j >= low && v[j] > key)
            {
                v[j + 1] = v[j];
                swaps++;
                j--;
            }
            v[j + 1] = key;
        }
        return;
    }
    int mid = low + (high - low) / 2;
    if (v[mid] < v[low])
    {
        swap(v[low], v[mid]);
        swaps++;
    }
    if (v[high] < v[low])
    {
        swap(v[low], v[high]);
        swaps++;
    }
    if (v[mid] < v[high])
    {
        swap(v[mid], v[high]);
        swaps++;
    }
    int pivot = v[high];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do { i++; } while (v[i] < pivot);
        do { j--; } while (v[j] > pivot);
        if (i >= j) break;
        swap(v[i], v[j]);
        swaps++;
    }
    bestQuickSort(v, swaps, low, j);
    bestQuickSort(v, swaps, j + 1, high);
}

void bestQuickSortWrapper(vector<int>& v, int& swaps)
{
    bestQuickSort(v, swaps);
}