#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>

uint32_t fibonacci_last_digit_naive(uint32_t n) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;

    for (uint32_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

uint32_t fibonacci_last_digit_fast(uint32_t n) {
    if (n <= 1)
        return n;

    uint64_t prev = 1;
    uint64_t curr = 1;

    for (uint64_t i = 2; i < n; i++) {
        uint64_t tmp = curr;
        curr = (curr + prev) % 10;
        prev = tmp;
    }
    return curr;
}

void test_solution() {
    assert(fibonacci_last_digit_fast(3) == 2);
    assert(fibonacci_last_digit_fast(10) == 5);
    for (uint32_t n = 0; n < 70; ++n) {
        std::cout << "Testing " << n << " :: "  << '\n';

        uint32_t fast = fibonacci_last_digit_fast(n);
        uint32_t naive = fibonacci_last_digit_naive(n);

        std::cout << "  --> " << fast << " <-> " << naive << '\n';
        assert(fast == naive);
    }
}

int32_t main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution();
    } else {
        uint32_t n = 0;
        std::cin >> n;
        std::cout << fibonacci_last_digit_fast(n) << '\n';
    }
    return 0;
}