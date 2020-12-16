#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 

using std::vector;
using std::string;
using std::max_element;
using std::min_element;
using std::stoi;

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
                int32_t tmp = (int32_t) this->get(i, j);
                if (tmp < 10) std::cout << " ";
                std::cout << tmp << " ";
                if (j == _m-1) std::cout << "\n";
            }
        }
#endif /*DEBUG*/
    }
};

template <class T>
void print_vector(const vector<T> &A) {
#ifdef DEBUG
    std::cout << "Printing vector of size " << A.size() << "\n";
    for (size_t i = 0; i < A.size(); i ++) {
        std::cout << A[i] << " ";
        if (i == A.size()-1) std::cout << "\n";
    }
#endif /*DEBUG*/
}

int64_t eval(int64_t a, char op, int64_t b) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

void set_min_max(size_t i, size_t j, vector<char> &ops, matrix<int64_t> &Min, matrix<int64_t> &Max) {
    vector<int64_t> R((j-i)*4, 0);
    size_t l = 0;
    for (size_t k = i; k < j; k++) {
        R[l] = eval( Min.get(i, k), ops[k], Min.get(k+1, j) );
        l++;
        R[l] = eval( Min.get(i, k), ops[k], Max.get(k+1, j) );
        l++;
        R[l] = eval( Max.get(i, k), ops[k], Min.get(k+1, j) );
        l++;
        R[l] = eval( Max.get(i, k), ops[k], Max.get(k+1, j) );
        l++;
    }
    print_vector<int64_t>(R);
    Min.set(i, j, *min_element(R.begin(), R.end()));
    Max.set(i, j, *max_element(R.begin(), R.end()));
}

int64_t place_parentheses(vector<int64_t> &nums, vector<char> &ops) {
    matrix<int64_t> Min(nums.size(), nums.size(), 0);
    matrix<int64_t> Max(nums.size(), nums.size(), 0);
    for (size_t d = 0; d < nums.size(); d++) {
        Min.set(d, d, nums[d]);
        Max.set(d, d, nums[d]);
    }

    for ( size_t d = 1; d < nums.size(); d++ ) {
        for ( size_t v = 0; v < nums.size()-d; v++ ) {
            set_min_max(v, v+d, ops, Min, Max);
        }
    }

    Max.print();
    Min.print();
    return Max.get(0, nums.size()-1);
}

int64_t get_maximum_value(const string &exp) {
    vector<int64_t> nums;
    vector<char> ops;
    for (size_t i = 0; i < exp.length(); i++) {
        int64_t tmp = stoi(exp.substr(i));
        nums.push_back(tmp);
        i++;
        if (tmp >= 10) i++;
        ops.push_back(exp[i]);
    }
    print_vector(nums);
    print_vector(ops);
    return place_parentheses(nums, ops);
}

void run_test(vector<int64_t> nums, vector<char> ops, int64_t output) {
    assert(place_parentheses(nums, ops) == output);
}

void test_solution(int64_t edje) {
    run_test({1, 2, 3, 4, 5}, {'+', '-', '*', '-'}, 6);
    run_test({1, 5}, {'+'}, 6);
    run_test({1, 2, 3, 4}, {'+', '+', '+'}, 10);
    run_test({1, 1, 3}, {'+', '*'}, 6);
    run_test({5, 8, 7, 4, 8, 9}, {'-', '+', '*', '-', '+'}, 200);
}

void proceed() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
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
