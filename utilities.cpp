#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct tableUnity
{
    string name;
    int vectorSize;
    long long time;
    bool sorted;
    int swaps;

    tableUnity(string name, int vectorSize, long long time, bool sorted, int swaps)
    {
        this->name = name;
        this->vectorSize = vectorSize;
        this->time = time;
        this->sorted = sorted;
        this->swaps = swaps;
    }
};

vector<int> generateRandomVector(size_t n)
{
    vector<int> vetor(n);
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distrib(0, 99); 
    for (int i = 0; i < n; i++)
    {
        vetor[i] = distrib(gen);
    }
    return vetor;
}

void printVector(vector<int> v)
{
    for (int num : v)
    {
        cout << num << " ";
    }
    cout << endl;
}
void printTableUnity(tableUnity t)
{
    string sorted;
    if(t.sorted)
        sorted = "sorted";
    else
        sorted = "not sorted";
    cout << t.name << " | Size: " << t.vectorSize << " | Time: " << t.time << " | " << sorted << " | Swaps: " << t.swaps << endl;
}

long long testAlgorithm(void (*sortFunction)(vector<int>&, int&), vector<int>& arr, int& swaps) {
    auto start = high_resolution_clock::now();
    sortFunction(arr, swaps);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    return duration.count();
}

bool isSorted(vector<int> v)
{
    return is_sorted(v.begin(), v.end());
}

vector<int> generateNearlySortedVector(size_t n) {
    if (n == 0) return {};
    vector<int> v(n);
    mt19937 rng(random_device{}());
    iota(v.begin(), v.end(), 1);
    size_t num_random = static_cast<size_t>(0.2 * n);
    vector<size_t> indices(n);
    iota(indices.begin(), indices.end(), 0);
    shuffle(indices.begin(), indices.end(), rng);
    for (size_t i = 0; i < num_random; i += 2) {
        if (i + 1 >= num_random) break;
        size_t a = indices[i];
        size_t b = indices[i + 1];
        swap(v[a], v[b]);
    }
    return v;
}

vector<int> generateInvertedSortedVectors(size_t n) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    reverse(v.begin(), v.end());
    return v;
}

void testRandomCases(
    const string& sortName,
    void (*sortFunction)(vector<int>&, int&),
    const vector<vector<int>>& randomVectors,
    vector<tableUnity>& randomTable
) {
    for(int i = 0; i < randomVectors.size(); i++) {
        vector<int> v = randomVectors[i];
        int swaps = 0;
        long long result = testAlgorithm(sortFunction, v, swaps);
        bool sorted = isSorted(v);
        randomTable.push_back(tableUnity(sortName, pow(10, i+1), result, sorted, swaps));
    }
}

void testNearlySortedCases(
    const string& sortName,
    void (*sortFunction)(vector<int>&, int&),
    const vector<vector<int>>& nearlySortedVectors,
    vector<tableUnity>& nearlySortedTable
) {
    for(int i = 0; i < nearlySortedVectors.size(); i++) {
        vector<int> v = nearlySortedVectors[i];
        int swaps = 0;
        long long result = testAlgorithm(sortFunction, v, swaps);
        bool sorted = isSorted(v);
        nearlySortedTable.push_back(tableUnity(sortName, pow(10, i+1), result, sorted, swaps));
    }
}

void testInvertedCases(
    const string& sortName,
    void (*sortFunction)(vector<int>&, int&),
    const vector<vector<int>>& invertedSortedVectors,
    vector<tableUnity>& invertedSortedTable
) {
    for(int i = 0; i < invertedSortedVectors.size(); i++) {
        vector<int> v = invertedSortedVectors[i];
        int swaps = 0;
        long long result = testAlgorithm(sortFunction, v, swaps);
        bool sorted = isSorted(v);
        invertedSortedTable.push_back(tableUnity(sortName, pow(10, i+1), result, sorted, swaps));
    }
}