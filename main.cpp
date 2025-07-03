#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "sortingAlgorithms.cpp"
#include "utilities.cpp"

using namespace std;
using namespace std::chrono;

int main()
{
    vector<tableUnity> randomTable = {};
    vector<tableUnity> nearlySortedTable = {};
    vector<tableUnity> invertedSortedTable = {};

    vector<vector<int>> randomVectors;
    vector<vector<int>> nearlySortedVectors;
    vector<vector<int>> invertedSortedVectors;
    vector<vector<int>> tempVectors;
    long long tempTime;
    bool sorted;
    int index = 0;
    int choice;

    int testSize = 4; //quantidade de vetores que serão testados

    for(int i = 1; i < testSize + 1; i++) //cria vetores de tamanho 10^i, então: 10, 100, 1000...
    {
        randomVectors.push_back(generateRandomVector(pow(10,i)));
    }

    for(int i = 1; i < testSize + 1; i++) //cria vetores de tamanho 10^i, então: 10, 100, 1000...
    {
        nearlySortedVectors.push_back(generateNearlySortedVector(pow(10,i)));
    }

    for(int i = 1; i < testSize + 1; i++) //cria vetores de tamanho 10^i, então: 10, 100, 1000...
    {
        invertedSortedVectors.push_back(generateInvertedSortedVectors(pow(10,i)));
    }
    
    for(index; index < 8; index++)
    {
        switch (index){
            case 0:
                testRandomCases("bubbleSort", bubbleSort, randomVectors, randomTable);
                testNearlySortedCases("bubbleSort", bubbleSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("bubbleSort", bubbleSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 1:
                testRandomCases("insertionSort", insertionSort, randomVectors, randomTable);
                testNearlySortedCases("insertionSort", insertionSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("insertionSort", insertionSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 2:
                testRandomCases("selectionSort", selectionSort, randomVectors, randomTable);
                testNearlySortedCases("selectionSort", selectionSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("selectionSort", selectionSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 3:
                testRandomCases("mergeSort", mergeSortWrapper, randomVectors, randomTable);
                testNearlySortedCases("mergeSort", mergeSortWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("mergeSort", mergeSortWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 4:
                testRandomCases("quickSortMiddle", quickSortMiddleWrapper, randomVectors, randomTable);
                testNearlySortedCases("quickSortMiddle", quickSortMiddleWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("quickSortMiddle", quickSortMiddleWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 5:
                testRandomCases("quickSortLeft", quickSortLeftWrapper, randomVectors, randomTable);
                testNearlySortedCases("quickSortLeft", quickSortLeftWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("quickSortLeft", quickSortLeftWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 6:
                testRandomCases("quickSortRight", quickSortRightWrapper, randomVectors, randomTable);
                testNearlySortedCases("quickSortRight", quickSortRightWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("quickSortRight", quickSortRightWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 7:
                testRandomCases("bestQuickSort", bestQuickSortWrapper, randomVectors, randomTable);
                testNearlySortedCases("bestQuickSort", bestQuickSortWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCases("bestQuickSort", bestQuickSortWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            default:
                break;
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "Random" << endl;
    for(tableUnity t : randomTable)
    {
        printTableUnity(t);
    }
    
    cout << "----------------------------------------" << endl;
    cout << "nearly sorted" << endl;

    for(tableUnity t : nearlySortedTable)
    {
        printTableUnity(t);
    }

    cout << "----------------------------------------" << endl;
    cout << "inverted sorted" << endl;

    for(tableUnity t : invertedSortedTable)
    {
        printTableUnity(t);
    }
}

