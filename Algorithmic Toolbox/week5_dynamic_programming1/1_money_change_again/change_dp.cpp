#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using std::vector;
using std::min_element;

vector<uint32_t> coin_types = {1, 3, 4};

void printvec(vector<uint32_t> vec) {
    std::cout << "[";
    for (uint32_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

uint32_t get_change(uint32_t m) {
    uint32_t offset = coin_types.back();
    vector<uint32_t> min_change_vec(m + offset + 1);
    for (uint32_t i = 0; i <= offset; i++) {
        min_change_vec[i] = m+1;
    }
    uint32_t k = 0 ;
    for (uint32_t i = 1 + offset; i <= m + offset; i++) {
        if (i - offset == coin_types[k]) {
            min_change_vec[i] = 1;
            k++;
        } else {
            vector<uint32_t> changes(coin_types.size());
            for (uint32_t j = 0; j < changes.size(); j++) {
                uint32_t pos = i - coin_types[j];
                changes[j] = min_change_vec[pos];
            }
            uint32_t min = *min_element(changes.begin(), changes.end());
            min_change_vec[i] = min + 1;
        }
    }
    return min_change_vec[m + offset];
}

uint32_t get_change_naive(uint32_t m) {
    uint32_t res = 0;
    uint32_t m_tmp = m;
    for (uint32_t i = 0; i < coin_types.size(); i++) {
        res += m_tmp / coin_types[i];
        m_tmp %= coin_types[i];
    }
    return res;
}

void test_solution(uint32_t edje) {
    assert(get_change(2)  == 2);
    assert(get_change(34) == 9);
}

void proceed() {
    uint32_t m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution(10);
    } else if (argc == 3 && strcmp(argv[1], "--stress") == 0 ) {
        uint32_t edje = std::stoi(argv[2]);
        test_solution(edje);
    } else {
        proceed();
    }
    return 0;
}