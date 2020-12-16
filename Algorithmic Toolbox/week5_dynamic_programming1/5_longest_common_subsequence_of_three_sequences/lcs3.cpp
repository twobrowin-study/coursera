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

static inline int64_t max7(int64_t a1, int64_t b1, int64_t c1,
                           int64_t a2, int64_t b2, int64_t c2,
                           int64_t a3) {
    int64_t a = max3(a1, b1, c1);
    int64_t b = max3(a2, b2, c2);
    return max3(a, b, a3);
}

int64_t lcs3(vector<int64_t> &a, vector<int64_t> &b, vector<int64_t> &c) {
    int64_t n = a.size() + 1;
    int64_t m = b.size() + 1;
    int64_t d = c.size() + 1;
    int64_t matr[n][m][d];

    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < m; j++) {
            for (int64_t k = 0; k < d; k++) {
                matr[i][j][k] = 0;
            }
        }
    }

    for (int64_t i = 1; i < n; i++) {
        for (int64_t j = 1; j < m; j++) {
            for (int64_t k = 1; k < d; k++) {
                int64_t diag = matr[i-1][j-1][k-1];
                if ( (a[i-1] == b[j-1]) && (b[j-1] == c[k-1]) ) {
                    diag++;
                }

                matr[i][j][k] = max7(
                    diag,
                    matr[i][j-1][k-1],
                    matr[i][j-1][k],
                    matr[i-1][j-1][k],
                    matr[i-1][j][k],
                    matr[i-1][j][k-1],
                    matr[i][j][k-1]
                );
            }
        }
    }

#ifdef DEBUG
    for (int64_t i = 0; i < n; i++) {
        if (i != 0) std::cout << a[i-1] << std::endl;
        std::cout << "     ";
        for (int64_t k = 1; k < d; k++) std::cout << c[k-1] << " ";
        std::cout << std::endl;

        std::cout << "   ";
        for (int64_t k = 1; k < d; k++) std::cout << "__";
        std::cout << "_" << std::endl;
        
        for (int64_t j = 0; j < m; j++) {
            if (j == 0) std::cout << "  |";
            if (j != 0) std::cout << b[j-1] << " |";
            for (int64_t k = 0; k < d; k++) {
                std::cout << matr[i][j][k];
                if (k != d-1) std::cout << " ";
                if (k == d-1) std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
#endif /* DEBUG */

    return matr[n-1][m-1][d-1];
}

static inline void test1() {
    vector<int64_t> a = {1, 2, 3};
    vector<int64_t> b = {2, 1, 3};
    vector<int64_t> c = {1, 3};
    int64_t res = lcs3(a, b, c);
    std::cout << res << "\n";
    assert( res == 2);
}

static inline void test2() {
    vector<int64_t> a = {8, 3, 2, 1, 7};
    vector<int64_t> b = {8, 2, 1, 3, 8, 9, 7};
    vector<int64_t> c = {6, 8, 3, 1, 4, 7};
    assert(lcs3(a, b, c) == 3);
}

void test_solution(int64_t edje) {
    test1();
    test2();
}

void proceed() {
    size_t an;
    std::cin >> an;
    vector<int64_t> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int64_t> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int64_t> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
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
