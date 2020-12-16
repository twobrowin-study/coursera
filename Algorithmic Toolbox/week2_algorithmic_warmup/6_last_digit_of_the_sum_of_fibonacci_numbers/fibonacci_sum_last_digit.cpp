#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t fibonacci_sum_naive(uint64_t n) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;
    uint64_t sum      = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
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

uint64_t fibonacci_sum_fast(uint64_t n) {
    if (n <= 1) {
        return n;
    }

    uint64_t pisano[62];
    uint64_t d = pisano_fast(10, pisano);

    uint64_t inner_sum = 0;
    for (uint64_t i = 0; i < n % d + 1; i++) {
        inner_sum += pisano[i];
    }

    uint64_t outer_sum = 0;
    if ( n / d > 0) {
        for (uint64_t i = 0; i < d; i++) {
            outer_sum += pisano[i];
        }
        outer_sum *= n / d;
    }

    return ( inner_sum + outer_sum ) % 10;
}

void test_solution() {
    assert(fibonacci_sum_fast(3) == 4);
    assert(fibonacci_sum_fast(100) == 5);

    for (uint64_t n = 0; n < 70; ++n) {
        std::cout << "Testing " << n << " :: "  << '\n';

        uint64_t fast = fibonacci_sum_fast(n);
        uint64_t naive = fibonacci_sum_naive(n);

        std::cout << "  --> " << fast << " <-> " << naive << '\n';
        assert(fast == naive);
    }
}

int32_t main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution();
    } else {
        uint64_t n = 0;
        std::cin >> n;
        std::cout << fibonacci_sum_fast(n) << '\n';
    }
    return 0;
}
