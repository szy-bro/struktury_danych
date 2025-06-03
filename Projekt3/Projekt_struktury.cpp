#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <chrono>
#include <random>
#include <algorithm> 

using namespace std;
using HashFunction = function<int(int, int)>;

class HashTable {
public:
    HashTable(int size, HashFunction func) : tableSize(size), hashFunc(func) {
        table.resize(tableSize);
    }

    void insert(int key) {
        int index = hashFunc(key, tableSize);
        table[index].push_back(key);
    }

    bool remove(int key) {
        int index = hashFunc(key, tableSize);
        auto& chain = table[index]; 

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {
                chain.erase(it);
                return true;
            }
        }
        return false; 
    }

    void populate(const vector<int>& data) {
        for (int key : data) {
            insert(key);
        }
    }

private:
    int tableSize;
    HashFunction hashFunc;
    vector<list<int>> table;
};


int hash1(int key, int size) {
    return abs(key) % size; 
}

int hash2(int key, int size) {
    return abs(key / 10) % size;
}


int hash3(int key, int size) {
    key = ((key >> 16) ^ key) * 0x45d9f3b; 
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key);
    return abs(key) % size;
}


vector<int> generateData(int n, const string& type, int tableSize, HashFunction currentHashFunc) {
    vector<int> data;
    random_device rd;
    mt19937 gen(rd()); 

    if (type == "optymistyczny") {
        uniform_int_distribution<> dist(1, 10000000); 
        for (int i = 0; i < n; ++i) {
            data.push_back(dist(gen));
        }
       
        shuffle(data.begin(), data.end(), gen);

    }
    else if (type == "sredni") {
    
        uniform_int_distribution<> dist(1, 1000000);
        for (int i = 0; i < n; ++i) {
            data.push_back(dist(gen));
        }
    }
    else if (type == "pesymistyczny") {

        for (int i = 0; i < n; ++i) {
            data.push_back(i * tableSize);
        }
    }
    return data;
}


void testHashFunction(HashFunction func, const string& name,
    const vector<int>& dataInsert,
    const vector<int>& dataRemove,
    const string& caseType,
    int tableSize) {


    HashTable ht_insert(tableSize, func);
    auto startInsert = chrono::high_resolution_clock::now();
    for (int key : dataInsert) {
        ht_insert.insert(key);
    }
    auto endInsert = chrono::high_resolution_clock::now();
    auto insertTime = chrono::duration_cast<chrono::microseconds>(endInsert - startInsert).count();

   
    HashTable ht_remove(tableSize, func);
    ht_remove.populate(dataInsert); 

    auto startRemove = chrono::high_resolution_clock::now();
    for (int key : dataRemove) {
        ht_remove.remove(key); 
    }
    auto endRemove = chrono::high_resolution_clock::now();
    auto removeTime = chrono::duration_cast<chrono::microseconds>(endRemove - startRemove).count();

    cout << "=== " << name << " | " << caseType << " ===\n";
    cout << "Czas dodawania: " << insertTime << " mikrosekund\n";
    cout << "Czas usuwania:  " << removeTime << " mikrosekund\n\n";
}

int main() {
    const int TABLE_SIZE = 10007;
    vector<string> cases = { "optymistyczny", "sredni", "pesymistyczny" };
    vector<int> testSizes = { 1000, 10000, 50000 };

    cout << "Porównanie operacji dodawania i usuwania w tablicach haszujących\n";
    cout << "Rozmiar tablicy haszującej: " << TABLE_SIZE << "\n\n";

    for (int N : testSizes) {
        cout << "# Test dla N = " << N << " elementow #\n";
      
        for (const auto& caseType : cases) {
       
      
            auto insertData1 = generateData(N, caseType, TABLE_SIZE, hash1);
            auto removeData1 = insertData1; 
            testHashFunction(hash1, "Hash 1: key % size", insertData1, removeData1, caseType, TABLE_SIZE);

            auto insertData2 = generateData(N, caseType, TABLE_SIZE, hash2);
            auto removeData2 = insertData2;
            testHashFunction(hash2, "Hash 2: (key / 10) % size", insertData2, removeData2, caseType, TABLE_SIZE);

            auto insertData3 = generateData(N, caseType, TABLE_SIZE, hash3);
            auto removeData3 = insertData3;
            testHashFunction(hash3, "Hash 3: XOR-Shift (uproszczony)", insertData3, removeData3, caseType, TABLE_SIZE);
        }
        cout << endl;
    }

    return 0;
}