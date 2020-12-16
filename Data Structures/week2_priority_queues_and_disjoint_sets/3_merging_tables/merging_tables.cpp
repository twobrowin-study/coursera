#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
        size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        int root = sets[table].parent;
        while(sets[root].parent != root) {
            root = sets[root].parent;
            sets[table].parent = root;
            table = root;
        }
        return root;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            auto &destTable = sets[realDestination];
            auto  &srcTable = sets[realSource];

            if (srcTable.rank > destTable.rank) {
                destTable.parent = srcTable.parent;
                srcTable.size += destTable.size;
                destTable.size = 0;
                max_table_size = max(max_table_size, srcTable.size);
            } else {
                srcTable.parent = destTable.parent;
                destTable.size += srcTable.size;
                srcTable.size = 0;
                max_table_size = max(max_table_size, destTable.size);
                if (srcTable.rank == destTable.rank) {
                    destTable.rank++;
                }
            }

        }		
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;
        
        tables.merge(destination, source);
            cout << tables.max_table_size << endl;
    }

    return 0;
}
