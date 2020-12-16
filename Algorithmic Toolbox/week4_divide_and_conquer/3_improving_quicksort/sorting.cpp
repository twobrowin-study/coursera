#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <algorithm>

using std::vector;
using std::swap;

void randomized_quick_sort(vector<int64_t> &a, int64_t l, int64_t r) {
    if (l >= r) {
        return;
    }

    int64_t k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);

    int64_t m = l;
    int64_t f = 0;
    int64_t x = a[l];
    for (int64_t i = l + 1; i <= r; i++) {
        if (a[i] == x) {
            m++;
            f++;
            swap(a[i], a[m]);
            swap(a[m], a[l+f]);
        } else if (a[i] < x) {
            m++;
            swap(a[i], a[m]);
        }
    }
    for (int64_t i = 0; i <= f; i++) {
        swap(a[l+i], a[m-i]);
    }

    randomized_quick_sort(a, l, m - f - 1);
    randomized_quick_sort(a, m + 1, r);
}

void test_solution(int64_t edje) {
    while (true) {
        int64_t n = (int64_t) (rand() % edje + 1);
        
        std::cout << "Vector of " << n << " : [";
        vector<int64_t> a(n);
        for (size_t i = 0; i < a.size(); i++) {
            a[i] = rand() % edje - edje;
            std::cout << a[i];
            if (i != a.size()-1) std::cout << ", ";
        }
        std::cout << "]...\n";

        vector<int64_t> sorted_a = a;
        sort(sorted_a.begin(), sorted_a.end());
        randomized_quick_sort(a, 0, a.size() - 1);

        std::cout << "\tSollution " << n << " : [";
        for (size_t i = 0; i < a.size(); i++) {
            std::cout << a[i];
            if (i != a.size()-1) std::cout << ", ";
        }
        std::cout << "]...\n";

        std::cout << "\tReal " << n << " : [";
        for (size_t i = 0; i < sorted_a.size(); i++) {
            std::cout << sorted_a[i];
            if (i != sorted_a.size()-1) std::cout << ", ";
        }
        std::cout << "]...\n";

        assert(a == sorted_a);

        std::cout << "\tOK\n";
    }
}

int main() {
    int64_t n;
    std::cin >> n;
    vector<int64_t> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
