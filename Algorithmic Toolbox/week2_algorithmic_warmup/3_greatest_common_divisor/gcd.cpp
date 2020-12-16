#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t gcd_naive(uint64_t a, uint64_t b) {
    uint64_t current_gcd = 1;
    for (uint64_t d = 2; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            if (d > current_gcd) {
                current_gcd = d;
            }
        }
    }
    return current_gcd;
}

uint64_t gcd_fast(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    }
    uint64_t an = a % b;
    return gcd_fast(b, an);
}

void test_solution(uint32_t edje) {
    assert(gcd_fast(2, 6) == 2);
    assert(gcd_fast(125, 17) == 1);

    while(true) {
        uint64_t a = rand() % edje;
        uint64_t b = rand() % edje;

        std::cout << "Testing " << a << " " << b << " :: "  << '\n';

        uint64_t fast = gcd_fast(a, b);
        uint64_t naive = gcd_naive(a, b);

        std::cout << "  --> " << fast << " <-> " << naive << '\n';
        assert(fast == naive);
    }
}

int32_t main(int argc, char* argv[]) {
    if (argc == 3 && strcmp(argv[1], "--stress") == 0 ) {
        uint32_t edje = std::stoi(argv[2]);
        test_solution(edje);
    } else {
        uint64_t a = 0;
        uint64_t b = 0;
        std::cin >> a >> b;
        std::cout << gcd_fast(a, b) << '\n';
    }
    return 0;
}
