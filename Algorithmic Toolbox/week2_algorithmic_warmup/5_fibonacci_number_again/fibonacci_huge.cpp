#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t fibonacci_huge_naive(uint64_t n, uint64_t m) {
    if (n <= 1) {
        return n;
    }

    uint64_t previous = 0;
    uint64_t current  = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

uint64_t fibonacci_huge_fast(uint64_t n, uint64_t m) {
    if (n <= 1) {
        return n;
    }

    uint64_t pi_arr[6*m+2] = {0};
    pi_arr[0] = 0;
    pi_arr[1] = 1;

    for(uint64_t i = 2; i < 6*m+3; i++) {
        if ( i > 2 && pi_arr[i-2] == 0 && pi_arr[i-1] == 1 ) {
            return pi_arr[n % (i-2)];
        }
        pi_arr[i] = (pi_arr[i-1] + pi_arr[i-2]) % m;
    }
    return 0;
}

void test_solution() {
    assert(fibonacci_huge_fast(239, 1000) == 161);
    assert(fibonacci_huge_fast(2816213588, 239) == 151);

    for (uint64_t n = 0; n < 70; ++n) {
        uint64_t m = rand() % 1000 + 2;
        std::cout << "Testing " << n << " " << m << " :: "  << '\n';

        uint64_t fast = fibonacci_huge_fast(n, m);
        uint64_t naive = fibonacci_huge_naive(n, m);

        std::cout << "  --> " << fast << " <-> " << naive << '\n';
        assert(fast == naive);
    }
}

int32_t main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution();
    } else {
        uint64_t n = 0;
        uint64_t m = 0;
        std::cin >> n >> m;
        std::cout << fibonacci_huge_fast(n, m) << '\n';
    }
    return 0;
}
