#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t lcm_naive(uint64_t a, uint64_t b) {
    for (uint64_t l = 1; l <= a * b; ++l) {
        if (l % a == 0 && l % b == 0) {
            return l;
        }
    }
    return a * b;
}

uint64_t gcd_fast(uint64_t a, uint64_t b) {
    if (b == 0) {
        return a;
    }
    uint64_t an = a % b;
    return gcd_fast(b, an);
}

uint64_t lcm_fast(uint64_t a, uint64_t b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    uint64_t gcd = gcd_fast(a, b);
    if (gcd == 1) {
        return a * b;
    } else {
        return a * b / gcd;
    }
}

void test_solution(uint32_t edje) {
    assert(lcm_fast(6, 8) == 24);
    assert(lcm_fast(761457, 614573) == 467970912861);

    while(true) {
        uint64_t a = rand() % edje;
        uint64_t b = rand() % edje;

        std::cout << "Testing " << a << " " << b << " :: "  << '\n';

        uint64_t fast = lcm_fast(a, b);
        uint64_t naive = lcm_naive(a, b);

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
        std::cout << lcm_fast(a, b) << '\n';
    }
    return 0;
}
