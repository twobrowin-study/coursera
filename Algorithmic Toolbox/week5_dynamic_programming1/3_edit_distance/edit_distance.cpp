#include <iostream>
#include <cassert>
#include <cstdint>
#include <string>

using std::string;

static inline uint32_t min3(uint32_t a, uint32_t b, uint32_t c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

uint32_t edit_distance(const string &str1, const string &str2) {
    uint32_t n = str1.length() + 1;
    uint32_t m = str2.length() + 1;
    uint32_t matr[n][m];
    uint32_t i;
    uint32_t j;

    j = 0;
    for (i = 0; i < n; i++) {
        matr[i][j] = i;
    }

    i = 0;
    for (j = 0; j < m; j++) {
        matr[i][j] = j;
    }

    for (i = 1; i < n; i++) {
        for (j = 1; j < m; j++) {
            uint32_t diag = matr[i-1][j-1];
            if (str1[i-1] != str2[j-1]) diag++;
            uint32_t res = min3(diag, matr[i-1][j]+1, matr[i][j-1]+1);
            matr[i][j] = res;
        }
    }

#ifdef DEBUG
    std::cout << "     ";
    for (j = 1; j < m; j++) std::cout << str2[j-1] << " ";
    std::cout << std::endl;

    std::cout << "   ";
    for (j = 1; j < m; j++) std::cout << "__";
    std::cout << "_" << std::endl;

    for (i = 0; i < n; i++) {
        if (i == 0) std::cout << "  |";
        if (i != 0) std::cout << str1[i-1] << " |";
        for (j = 0; j < m; j++) {
            std::cout << matr[i][j];
            if (j != m-1) std::cout << " ";
            if (j == m-1) std::cout << std::endl;
        }
    }
    std::cout << std::endl;
#endif /* DEBUG */

    return matr[n-1][m-1];
}

void test_solution(uint32_t edje) {
    assert(edit_distance("ab", "ab") == 0);
    assert(edit_distance("short", "ports") == 3);
    assert(edit_distance("editing", "distance") == 5);
}
void proceed() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc >= 2 && string(argv[1]) == "--stress") {
        if (argc == 2) test_solution(10);
        else test_solution(
                std::stoi( string(argv[2]) )
             );
    } else {
        proceed();
    }
    return 0;
}