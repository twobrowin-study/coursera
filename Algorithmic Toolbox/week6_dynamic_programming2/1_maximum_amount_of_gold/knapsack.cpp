#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>

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
                std::cout << this->get(i, j) << " ";
                if (j == _m-1) std::cout << "\n";
            }
        }
#endif /*DEBUG*/
    }
};

uint32_t optimal_weight(uint32_t W, const vector<uint32_t> &w) {
    matrix<uint32_t> values(w.size()+1, W+1, 0);
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
    values.print();
    return values.get(w.size(), W);
}

void test_solution(uint32_t edje) {
    vector<uint32_t> w = {1, 4, 8};
    assert(optimal_weight(10, w) == 9);
}

void proceed() {
    uint32_t n, W;
    std::cin >> W >> n;
    vector<uint32_t> w(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
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