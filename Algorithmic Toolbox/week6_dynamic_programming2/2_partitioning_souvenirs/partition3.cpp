#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;

template <class T>
class matrix {
private:
    std::vector<T> _data;
    std::size_t _n;
    std::size_t _m;

public:
    matrix (std::size_t n, std::size_t m, T vals) : _n(n), _m(m), _data(n*m, vals) {}
    std::size_t size() { return _data.size(); }
    T get (std::size_t i, std::size_t j) { return _data[_m*i+j]; }
    void set (std::size_t i, std::size_t j, T val) { _data[_m*i+j] = val; }

    void print() {
#ifdef DEBUG
        std::cout << "Printing matrix of size " << this->size() << "\n";
        for (size_t i = 0; i < _n; i++) {
            for (size_t j = 0; j < _m; j++) {
                uint32_t tmp = (uint32_t) this->get(i, j);
                if (tmp < 10) std::cout << " ";
                std::cout << tmp << " ";
                if (j == _m-1) std::cout << "\n";
            }
        }
#endif /*DEBUG*/
    }
};

void print_vector(const vector<uint32_t> &A) {
#ifdef DEBUG
    std::cout << "Printing vector of size " << A.size() << "\n";
    for (size_t i = 0; i < A.size(); i ++) {
        std::cout << A[i] << " ";
        if (i == A.size()-1) std::cout << "\n";
    }
#endif /*DEBUG*/
}

uint32_t knapsack(uint32_t W, const vector<uint32_t> &w, matrix<uint32_t> &values) {
    for (size_t i = 1; i <= w.size(); i++) {
        for (size_t j = 1; j <= W; j++) {
            uint32_t tmp = values.get(i-1, j);
            values.set(i, j, tmp);
            if (w[i-1] <= j) {
                uint32_t tmp = values.get(i-1, j-w[i-1]);
                uint32_t new_val = tmp + w[i-1];
                if ( new_val >= values.get(i,j) ) {
                    values.set(i, j, new_val);
                }
            }
        }
    }
    return values.get(w.size(), W);
}

vector<uint32_t> knapsack_reconstruct(uint32_t W, const vector<uint32_t> &w, matrix<uint32_t> &values) {
    vector<uint32_t> res;
    for (size_t j = W; j != 0;) {
        for (size_t i = w.size(); i >= 1; i--) {
            if (w[i-1] <= j) {
                uint32_t tmp = values.get(i-1, j-w[i-1]);
                uint32_t test_val = tmp + w[i-1];
                if ( test_val == values.get(i, j) ) {
                    res.push_back(i-1);
                    j -= w[i-1];
                }
            }
        }
    }
    return res;
}

uint32_t partition3(vector<uint32_t> &A) {
    std::sort(A.begin(), A.end());
    print_vector(A);
    uint32_t sum = std::accumulate(A.begin(), A.end(), 0);
    if (sum % 3 != 0) {
        return 0;
    }
    uint32_t W = sum / 3;

    vector<uint32_t> w = A;
    for (uint32_t l = 0; l < 3; l++) {
        matrix<uint32_t> values(w.size()+1, W+1, 0);
        uint32_t res = knapsack(W, w, values);
        values.print();
        if (res != W) {
            return 0;
        }
        vector<uint32_t> to_del = knapsack_reconstruct(W, w, values);
        print_vector(to_del);
        for (size_t k = 0; k < to_del.size(); k++) {
            w.erase(w.begin() + to_del[k]);
        }
        print_vector(w);
    }

    if (w.size() != 0) {
        return 0;
    }

    return 1;
}

void run_test(vector<uint32_t> sample, uint32_t output) {
    assert(partition3(sample) == output);
}

void test_solution(uint32_t edje) {
    run_test({3, 3, 3, 3}, 0);
    run_test({3, 3, 3}, 1);
    run_test({40}, 0);
    run_test({17, 59, 34, 57, 17, 23, 67, 1, 18, 2, 59}, 1);
    run_test({1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25}, 1);
}

void proceed() {
    uint32_t n;
    std::cin >> n;
    vector<uint32_t> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
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