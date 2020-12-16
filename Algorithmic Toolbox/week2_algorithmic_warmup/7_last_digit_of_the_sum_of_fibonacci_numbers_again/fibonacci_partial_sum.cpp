#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t fibonacci_partial_sum_naive(uint64_t from, uint64_t to) {
    uint64_t sum = 0;

    uint64_t current = 0;
    uint64_t next  = 1;

    for (uint64_t i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        uint64_t new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

uint64_t pisano_fast(uint64_t m, uint64_t* pisano) {
    if (m < 2) {
        return 0;
    }

    pisano[0] = 0;
    pisano[1] = 1;

    for(uint64_t i = 2; i < 6*m+3; i++) {
        if ( i > 2 && pisano[i-2] == 0 && pisano[i-1] == 1 ) {
            return i-2;
        }
        pisano[i] = (pisano[i-1] + pisano[i-2]) % m;
    }
    return 0;
}

uint64_t fibonacci_partial_sum_fast(uint64_t from, uint64_t to) {
    uint64_t pisano[62];
    uint64_t d = pisano_fast(10, pisano);

    if ( to - from <= d) {
        uint64_t sum = 0;
        for (uint64_t i = from % d; i <= to % d; i++) {
            sum += pisano[i];
        }
        return sum % 10;
    }

    uint64_t start_sum = 0;
    for (uint64_t i = from % d; i < d; i++) {
        start_sum += pisano[i];
    }

    uint64_t stop_sum = 0;
    for (uint64_t i = 0; i <= to % d; i++) {
        stop_sum += pisano[i];
    }

    uint64_t inner_sum = 0;
    if ( (to - from) / d > 0 ) {
        for (uint64_t i = 0; i < d; i++) {
            inner_sum += pisano[i];
        }
        inner_sum *= (to - from) / d;
    }

    return (start_sum + inner_sum + stop_sum) % 10;
}

void test_solution() {
    assert(fibonacci_partial_sum_fast(3, 7) == 1);
    assert(fibonacci_partial_sum_fast(10, 10) == 5);
    assert(fibonacci_partial_sum_fast(10, 200) == 2);

    while (true) {
        uint64_t from = rand() % 10;
        uint64_t to = from + rand() % 10;

        std::cout << "Testing " << from << " " << to << " :: "  << '\n';

        uint64_t fast = fibonacci_partial_sum_fast(from, to);
        uint64_t naive = fibonacci_partial_sum_naive(from, to);

        std::cout << "  --> " << fast << " <-> " << naive << '\n';
        assert(fast == naive);
    }
}

int32_t main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution();
    } else {
        uint64_t from = 0;
        uint64_t to = 0;
        std::cin >> from >> to;
        std::cout << fibonacci_partial_sum_fast(from, to) << '\n';
    }
    return 0;
}
