#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct tableUnity
{
    string name;
    int vectorSize;
    long long time;
    bool sorted;
    long long swaps;
    long long comparisons;

    tableUnity(string name, int vectorSize, long long time, bool sorted, long long swaps, long long comparisons)
    {
        this->name = name;
        this->vectorSize = vectorSize;
        this->time = time;
        this->sorted = sorted;
        this->swaps = swaps;
        this->comparisons = comparisons;
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
    cout << t.name << " | Size: " << t.vectorSize << " | Time: " << t.time << " | " << sorted << " | Swaps: " << t.swaps << " | Comparisons: " << t.comparisons << endl;
}

long long testAlgorithm(void (*sortFunction)(vector<int>&, long long&, long long&), vector<int>& arr, long long& swaps, long long& comparisons)
{
    auto start = high_resolution_clock::now();
    sortFunction(arr, swaps, comparisons);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

bool isSorted(vector<int> v)
{
    return is_sorted(v.begin(), v.end());
}

vector<int> generateNearlySortedVector(size_t n)
{
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

vector<int> generateInvertedSortedVectors(size_t n)
{
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    reverse(v.begin(), v.end());
    return v;
}

void testRandomCasesAvg(
    const string& sortName,
    void (*sortFunction)(vector<int>&, long long&, long long&),
    const vector<vector<int>>& randomVectors,
    vector<tableUnity>& randomTable
)
{
    int repetitions = 5;
    for(int i = 0; i < randomVectors.size(); i++)
    {
        std::vector<long long> times;
        std::vector<long long> swapsVec;
        std::vector<long long> compsVec;
        bool allSorted = true;
        for(int rep = 0; rep < repetitions; rep++)
        {
            vector<int> v = randomVectors[i];
            long long swaps = 0, comparisons = 0;
            long long result = testAlgorithm(sortFunction, v, swaps, comparisons);
            times.push_back(result);
            swapsVec.push_back(swaps);
            compsVec.push_back(comparisons);
            allSorted = allSorted && isSorted(v);
        }
        sort(times.begin(), times.end());
        sort(swapsVec.begin(), swapsVec.end());
        sort(compsVec.begin(), compsVec.end());
        long long medianTime = times[repetitions / 2];
        long long medianSwaps = swapsVec[repetitions / 2];
        long long medianComps = compsVec[repetitions / 2];
        randomTable.push_back(tableUnity(
            sortName,
            pow(10, i+1),
            medianTime,
            allSorted,
            medianSwaps,
            medianComps
        ));
    }
}

void testNearlySortedCasesAvg(
    const string& sortName,
    void (*sortFunction)(vector<int>&, long long&, long long&),
    const vector<vector<int>>& nearlySortedVectors,
    vector<tableUnity>& nearlySortedTable
)
{
    int repetitions = 5;
    for(int i = 0; i < nearlySortedVectors.size(); i++)
    {
        std::vector<long long> times;
        std::vector<long long> swapsVec;
        std::vector<long long> compsVec;
        bool allSorted = true;
        for(int rep = 0; rep < repetitions; rep++)
        {
            vector<int> v = nearlySortedVectors[i];
            long long swaps = 0;
            long long comparisons = 0;
            long long result = testAlgorithm(sortFunction, v, swaps, comparisons);
            times.push_back(result);
            swapsVec.push_back(swaps);
            compsVec.push_back(comparisons);
            allSorted = allSorted && isSorted(v);
        }
        std::sort(times.begin(), times.end());
        std::sort(swapsVec.begin(), swapsVec.end());
        long long medianTime = times[repetitions / 2];
        long long medianSwaps = swapsVec[repetitions / 2];
        long long medianComps = compsVec[repetitions / 2];
        nearlySortedTable.push_back(tableUnity(
            sortName,
            pow(10, i+1),
            medianTime,
            allSorted,
            medianSwaps,
            medianComps
        ));
    }
}

void testInvertedCasesAvg(
    const string& sortName,
    void (*sortFunction)(vector<int>&, long long&, long long&),
    const vector<vector<int>>& invertedSortedVectors,
    vector<tableUnity>& invertedSortedTable
)
{
    int repetitions = 5;
    for(int i = 0; i < invertedSortedVectors.size(); i++)
    {
        vector<long long> times;
        vector<long long> swapsVec;
        vector<long long> compsVec;
        bool allSorted = true;
        for(int rep = 0; rep < repetitions; rep++)
        {
            vector<int> v = invertedSortedVectors[i];
            long long swaps = 0, comparisons = 0;
            long long result = testAlgorithm(sortFunction, v, swaps, comparisons);
            times.push_back(result);
            swapsVec.push_back(swaps);
            compsVec.push_back(comparisons);
            allSorted = allSorted && isSorted(v);
        }
        sort(times.begin(), times.end());
        sort(swapsVec.begin(), swapsVec.end());
        sort(compsVec.begin(), compsVec.end());
        long long medianTime = times[repetitions / 2];
        long long medianSwaps = swapsVec[repetitions / 2];
        long long medianComps = compsVec[repetitions / 2];
        invertedSortedTable.push_back(tableUnity(
            sortName,
            pow(10, i+1),
            medianTime,
            allSorted,
            medianSwaps,
            medianComps
        ));
    }
}

void printTableTime(vector<tableUnity> table, string name, int repetitions)
{
    ofstream csvFile("tables/" + name + ".csv");
    int algCount = table.size() / repetitions;

    csvFile << "Tamanho do vetor,";

    for(int i = 0; i < algCount; i++)
    {
        csvFile << table[i * repetitions].name;
        if(i + 1 < algCount)
            csvFile << ",";
        else
            csvFile << endl;
    }
    for(int rep = 0; rep < repetitions; rep++)
    {
        csvFile << pow(10,rep+1) << ",";
        for(int alg = 0; alg < algCount; alg++)
        {
            csvFile << table[alg * repetitions + rep].time;
            if(alg + 1 < algCount)
                csvFile << ",";
            else
                csvFile << endl;
        }
    }
}

void printTableSwaps(vector<tableUnity> table, string name, int repetitions)
{
    ofstream csvFile("tables/" + name + ".csv");
    int algCount = table.size() / repetitions;

    csvFile << "Tamanho do vetor,";

    for(int i = 0; i < algCount; i++)
    {
        csvFile << table[i * repetitions].name;
        if(i + 1 < algCount)
            csvFile << ",";
        else
            csvFile << endl;
    }
    
    for(int rep = 0; rep < repetitions; rep++)
    {
        csvFile << pow(10,rep+1) << ",";
        for(int alg = 0; alg < algCount; alg++)
        {
            csvFile << table[alg * repetitions + rep].swaps;
            if(alg + 1 < algCount)
                csvFile << ",";
            else
                csvFile << endl;
        }
    }
}

void printTableComps(vector<tableUnity> table, string name, int repetitions)
{
    ofstream csvFile("tables/" + name + ".csv");
    int algCount = table.size() / repetitions;

    csvFile << "Tamanho do vetor,";

    for(int i = 0; i < algCount; i++)
    {
        csvFile << table[i * repetitions].name;
        if(i + 1 < algCount)
            csvFile << ",";
        else
            csvFile << endl;
    }

    for(int rep = 0; rep < repetitions; rep++)
    {
        csvFile << pow(10,rep+1) << ",";
        for(int alg = 0; alg < algCount; alg++)
        {
            csvFile << table[alg * repetitions + rep].comparisons;
            if(alg + 1 < algCount)
                csvFile << ",";
            else
                csvFile << endl;
        }
    }
}