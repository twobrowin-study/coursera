#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <string>

using std::vector;

static inline int64_t max3(int64_t a, int64_t b, int64_t c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int64_t lcs2(vector<int64_t> &a, vector<int64_t> &b) {
    int64_t n = a.size() + 1;
    int64_t m = b.size() + 1;
    int64_t matr[n][m] = {0};

    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) {
            matr[i][j] = 0;
        }
    }

    for (int64_t i = 1; i < n; i++) {
        for (int64_t j = 1; j < m; j++) {
            int64_t diag = matr[i-1][j-1];
            int64_t right = matr[i][j-1];
            int64_t down = matr[i-1][j];

            if (a[i-1] == b[j-1]) {
                diag++;
            }

            matr[i][j] = max3(right, down, diag);
        }
    }

#ifdef DEBUG
    std::cout << "     ";
    for (int64_t j = 1; j < m; j++) std::cout << b[j-1] << " ";
    std::cout << std::endl;

    std::cout << "   ";
    for (int64_t j = 1; j < m; j++) std::cout << "__";
    std::cout << "_" << std::endl;

    for (int64_t i = 0; i < n; i++) {
        if (i == 0) std::cout << "  |";
        if (i != 0) std::cout << a[i-1] << " |";
        for (int64_t j = 0; j < m; j++) {
            std::cout << matr[i][j];
            if (j != m-1) std::cout << " ";
            if (j == m-1) std::cout << std::endl;
        }
    }
    std::cout << std::endl;
#endif /* DEBUG */

    return matr[n-1][m-1];
}

static inline void test1() {
    vector<int64_t> a = {2, 7, 5};
    vector<int64_t> b = {2, 5};
    assert(lcs2(a, b) == 2);
}

static inline void test2() {
    vector<int64_t> a = {7};
    vector<int64_t> b = {1, 2, 3, 4};
    assert(lcs2(a, b) == 0);
}

static inline void test3() {
    vector<int64_t> a = {2, 7, 8 ,3};
    vector<int64_t> b = {5, 2, 8, 7};
    assert(lcs2(a, b) == 2);
}

static inline void test4() {
    vector<int64_t> a = {-1, 0, 3, -5};
    vector<int64_t> b = {0, 2, 2, -5};
    assert(lcs2(a, b) == 2);
}

static inline void test5() {
    vector<int64_t> a = {1, 1, 2};
    vector<int64_t> b = {1, 2};
    assert(lcs2(a, b) == 2);
}

void test_solution(int64_t edje) {
    test1();
    test2();
    test3();
    test4();
    test5();
}

void proceed() {
    size_t n;
    std::cin >> n;
    vector<int64_t> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int64_t> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc >= 2 && std::string(argv[1]) == "--stress") {
        if (argc == 2) test_solution(10);
        else test_solution(
                std::stoi( std::string(argv[2]) )
             );
    } else {
        proceed();
    }
    return 0;
}
