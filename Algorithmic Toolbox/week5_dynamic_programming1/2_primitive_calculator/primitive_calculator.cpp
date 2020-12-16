#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <climits>

using std::vector;

typedef struct {
    uint32_t num_of_ops;
    uint32_t next_int;
} step_t;

void printvec(vector<step_t> vec) {
    std::cout << "[";
    for (uint32_t i = 0; i < vec.size(); i++) {
        std::cout << "{" << vec[i].num_of_ops;
        std::cout << ", " << vec[i].next_int << "}";
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void printvec(vector<uint32_t> vec) {
    std::cout << "[";
    for (uint32_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

vector<uint32_t> optimal_sequence_greedy(uint32_t n) {
    vector<uint32_t> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

vector<uint32_t> optimal_sequence(uint32_t n) {
    step_t init = {UINT_MAX, 0};
    vector<step_t> steps(n+1, init);
    steps[n] = {0, 0};

    for (uint32_t i = n; i > 1; i--) {
        uint32_t s = steps[i].num_of_ops + 1;
        if ( (i%3 == 0) && (steps[i/3].num_of_ops > s) ) {
            steps[i/3] = {s, i};
        }
        if ( (i%2 == 0) && (steps[i/2].num_of_ops > s) ) {
            steps[i/2] = {s, i};
        }
        if (steps[i-1].num_of_ops > s) {
            steps[i-1] = {s, i};
        }
    }

    vector<uint32_t> sequence(steps[1].num_of_ops+1);
    uint32_t j = 0;
    for (uint32_t i = 1; i != 0; i = steps[i].next_int) {
        sequence[j] = i;
        j++;
    }

    return sequence;
}

void test_solution(uint32_t edje) {
    assert(optimal_sequence(1).size()-1 == 0);
    assert(optimal_sequence(5).size()-1 == 3);
    assert(optimal_sequence(96234).size()-1 == 14);
}

void proceed() {
    uint32_t n;
    std::cin >> n;
    vector<uint32_t> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
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