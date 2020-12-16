#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>

using std::vector;

int64_t binary_search(const vector<int64_t> &a, int64_t x, int64_t left, int64_t right) {
    if ( (left > right) || (right < left) ) {
        return -1;
    }

    int64_t center = (left + right) / 2;

    if ( x == a[center] ) {
        return center;
    } else if ( x > a[center] ) {
        return binary_search(a, x, center+1, right);
    } else if ( x < a[center] ) {
        return binary_search(a, x, left, center-1);
    }

    return -1;
}

int64_t inline binary_search(const vector<int64_t> &a, int64_t x) {
    return binary_search(a, x, 0, a.size()-1);
}

int64_t linear_search(const vector<int64_t> &a, int64_t x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

void test_solution(int64_t edje) {
    while (true) {
        uint64_t n = (uint64_t) (rand() % edje + 1);
        
        std::cout << "Vector of " << n << " : [";
        vector<int64_t> a(n);
        a[0] = (uint64_t) (rand() % edje + 1);
        std::cout << a[0] << ", ";
        for (size_t i = 1; i < a.size(); i++) {
            a[i] = a[i-1] + (uint64_t) (rand() % edje + 1);
            std::cout << a[i];
            if (i != a.size()-1) std::cout << ", ";
        }
        std::cout << "]...\n";

        uint64_t m = (uint64_t) (rand() % edje + 1);
        vector<int64_t> b(m);
        for (int64_t i = 0; i < b.size(); ++i) {
            b[i] = (uint64_t) (rand() % edje + 1);
        }

        for (int64_t i = 0; i < b.size(); ++i) {
            std::cout << "\tSearching for " << b[i] << "\n";
            
            int64_t linear = linear_search(a, b[i]);
            int64_t binary = binary_search(a, b[i]);

            std::cout << "\t\tLinear :: " << linear << "\n";
            std::cout << "\t\tBinary :: " << binary << "\n";
            
            assert(linear == binary);

            std::cout << "\t\tOK\n\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution(100);
    } else {
        uint64_t n;
        std::cin >> n;
        
        vector<int64_t> a(n);
        for (size_t i = 0; i < a.size(); i++) {
            std::cin >> a[i];
        }
        
        uint64_t m;
        std::cin >> m;
        
        vector<int64_t> b(m);
        for (int64_t i = 0; i < b.size(); ++i) {
            std::cin >> b[i];
        }
        
        for (int64_t i = 0; i < b.size(); ++i) {
            std::cout << binary_search(a, b[i]) << ' ';
        }
    }
    return 0;
}
