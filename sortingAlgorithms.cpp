#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//note que em geral, as comparações só são aumentadas quando há uma comparação entre ELEMENTOS do vetor, e não quando há comparações nos parenteses do for-loop por exemplo
//As trocas só são aumentadas quando há uma troca de ELEMENTOS do vetor, e não quando há uma troca de variáveis auxiliares, como no caso do insertionSort por exemplo
void bubbleSort(vector<int>& v, long long& swaps, long long& comparisons) //bubbleSort padrão, porém com a contagem de trocas e comparações
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


void insertionSort(vector<int>& v, long long& swaps, long long& comparisons) //insertionSort padrão, porém com a contagem de trocas e comparações
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

void selectionSort(vector<int>& v, long long& swaps, long long& comparisons)//selectionSort padrão, porém com a contagem de trocas e comparações
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

void merge(vector<int>& v, int left, int mid, int right, long long& comparisons) //merge, a função auxiliar do mergeSort, porem levando em consideração as comparações
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

void mergeSort(vector<int>& v, int left, int right, long long& swaps, long long& comparisons) //mergeSort padrão, porém com a contagem de trocas e comparações
{
    swaps = 0; //não são feitas trocas na mergeSort
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(v, left, mid, swaps, comparisons);
    mergeSort(v, mid + 1, right, swaps, comparisons);
    merge(v, left, mid, right, comparisons);
}

void mergeSortWrapper(vector<int>& v, long long& swaps, long long& comparisons) //apenas um wrapper para facilitar a chamada da mergeSort nas funções de testar os algoritmos
{
    mergeSort(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortMiddle(vector<int>& v, int left, int right, long long& swaps, long long& comparisons) //quickSort com o pivô sendo o elemento do meio, porém com a contagem de trocas e comparações
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

void quickSortMiddleWrapper(vector<int>& v, long long& swaps, long long& comparisons) //apenas um wrapper para facilitar a chamada da quickSortMiddle nas funções de testar os algoritmos
{
    quickSortMiddle(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortLeft(vector<int>& v, int left, int right, long long& swaps, long long& comparisons) //quickSort com o pivô sendo o elemento da esquerda, porém com a contagem de trocas e comparações
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

void quickSortLeftWrapper(vector<int>& v, long long& swaps, long long& comparisons) //apenas um wrapper para facilitar a chamada da quickSortLeft nas funções de testar os algoritmos
{
    quickSortLeft(v, 0, v.size() - 1, swaps, comparisons);
}

void quickSortRight(vector<int>& v, int left, int right, long long& swaps, long long& comparisons) //quickSort com o pivô sendo o elemento da direita, porém com a contagem de trocas e comparações
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

void quickSortRightWrapper(vector<int>& v, long long& swaps, long long& comparisons)  //apenas um wrapper para facilitar a chamada da quickSortRight nas funções de testar os algoritmos
{
    quickSortRight(v, 0, v.size() - 1, swaps, comparisons);
}

void bestQuickSort(vector<int>& v, long long& swaps, long long& comparisons, int low = 0, int high = -1) //bestQuickSort é o apelido para a quickSort com o pivô mediana de 3
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
    comparisons++;
    if (v[mid] < v[low])
    {
        swap(v[low], v[mid]);
        swaps++;
    }
    comparisons++;
    if (v[high] < v[low])
    {
        swap(v[low], v[high]);
        swaps++;
    }
    comparisons++;
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
        do
        {
            i++;
            comparisons++;
        } while (v[i] < pivot);
        do
        {
            j--;
            comparisons++;
        } while (v[j] > pivot);
        if (i >= j) break;
        swap(v[i], v[j]);
        swaps++;
    }
    bestQuickSort(v, swaps, comparisons, low, j);
    bestQuickSort(v, swaps, comparisons, j + 1, high);
}

void bestQuickSortWrapper(vector<int>& v, long long& swaps, long long& comparisons) //apenas um wrapper para facilitar a chamada da bestQuickSort nas funções de testar os algoritmos
{
    bestQuickSort(v, swaps, comparisons);
}

void sortWrapper(vector<int>& v, long long& swaps, long long& comparisons) //apenas um wrapper para facilitar a chamada da std::sort nas funções de testar os algoritmos
{
    swaps = 0; //não é possivel testar as trocas da std::sort, pois ela não fornece essa informação
    comparisons = 0; //nao é possivel testar as comparações da std::sort, pois ela não fornece essa informação
    sort(v.begin(), v.end());
}