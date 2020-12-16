#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>

uint64_t fibonacci_naive(uint64_t n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

uint64_t fibonacci_fast(uint64_t n) {
    if (n <= 1)
        return n;

    uint64_t prev = 1;
    uint64_t curr = 1;

    for (uint64_t i = 2; i < n; i++) {
        uint64_t tmp = curr;
        curr = curr + prev;
        prev = tmp;
    }
    return curr;
}

void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (uint64_t n = 0; n < 25; ++n) {
        std::cout << "Testing " << n << " :: "  << '\n';

        uint64_t fast = fibonacci_fast(n);
        uint64_t naive = fibonacci_naive(n);

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
        std::cout << fibonacci_fast(n) << '\n';
    }
    return 0;
}
