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
    
    for(index; index < 9; index++)
    {
        switch (index){
            case 0:
                testRandomCasesAvg("bubbleSort", bubbleSort, randomVectors, randomTable);
                testNearlySortedCasesAvg("bubbleSort", bubbleSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("bubbleSort", bubbleSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 1:
                testRandomCasesAvg("insertionSort", insertionSort, randomVectors, randomTable);
                testNearlySortedCasesAvg("insertionSort", insertionSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("insertionSort", insertionSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 2:
                testRandomCasesAvg("selectionSort", selectionSort, randomVectors, randomTable);
                testNearlySortedCasesAvg("selectionSort", selectionSort, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("selectionSort", selectionSort, invertedSortedVectors, invertedSortedTable);
                break;
            case 3:
                testRandomCasesAvg("mergeSort", mergeSortWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("mergeSort", mergeSortWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("mergeSort", mergeSortWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 4:
                testRandomCasesAvg("quickSortMiddle", quickSortMiddleWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("quickSortMiddle", quickSortMiddleWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("quickSortMiddle", quickSortMiddleWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 5:
                testRandomCasesAvg("quickSortLeft", quickSortLeftWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("quickSortLeft", quickSortLeftWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("quickSortLeft", quickSortLeftWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 6:
                testRandomCasesAvg("quickSortRight", quickSortRightWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("quickSortRight", quickSortRightWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("quickSortRight", quickSortRightWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 7:
                testRandomCasesAvg("bestQuickSort", bestQuickSortWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("bestQuickSort", bestQuickSortWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("bestQuickSort", bestQuickSortWrapper, invertedSortedVectors, invertedSortedTable);
                break;
            case 8:
                testRandomCasesAvg("std::sort", sortWrapper, randomVectors, randomTable);
                testNearlySortedCasesAvg("std::sort", sortWrapper, nearlySortedVectors, nearlySortedTable);
                testInvertedCasesAvg("std::sort", sortWrapper, invertedSortedVectors, invertedSortedTable );
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

    printTableTime(randomTable, "randomTableTime", testSize);
    printTableTime(nearlySortedTable, "nearlySortedTableTime", testSize);
    printTableTime(invertedSortedTable, "inverteSortedtableTime", testSize);
    
    printTableSwaps(randomTable, "randomTableSwaps", testSize);
    printTableSwaps(nearlySortedTable, "nearlySortedTableSwaps", testSize);
    printTableSwaps(invertedSortedTable, "inverteSortedtableSwaps", testSize);

    printTableComps(randomTable, "randomTableComps", testSize);
    printTableComps(nearlySortedTable, "nearlySortedTableSComps", testSize);
    printTableComps(invertedSortedTable, "inverteSortedtableComps", testSize);

    return 0;
}

