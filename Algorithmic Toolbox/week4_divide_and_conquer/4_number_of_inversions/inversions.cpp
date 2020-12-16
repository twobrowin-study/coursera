#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdlib.h>
#include <vector>

using std::vector;

int64_t get_number_of_inversions(vector<int64_t>& a, size_t left, size_t right) {
    if (left + 1 >= right) return 0;
    size_t awe = (left + right) / 2;
    
    int64_t number_of_inversions = 0;
    number_of_inversions += get_number_of_inversions(a, left, awe);
    number_of_inversions += get_number_of_inversions(a, awe, right);

    vector<int64_t> b(right-left);
    size_t p_left = left;
    size_t p_right = awe;
    for (size_t i = 0; i < right-left; i++) {
        if (p_left < awe && p_right < right) {
            std::cout << "Comparing " << a[p_left] << " and " << a[p_right] << "\n";
            // if ( (p_left < awe-1) && (a[p_left] > a[p_right]) ) {
            //     std::cout << "\tSwap " << a[p_left] << " and " << a[p_right] << "\n";
            //     number_of_inversions++;
            // }
        }
        else if (p_left < awe) {
            std::cout << "Writing Left " << a[p_left] << "\n";
            // number_of_inversions++;
        }
        else if (p_right < right) {
            std::cout << "Writing Right " << a[p_right] << "\n";
        }

        if ( (p_left >= awe) && (p_right < right) ) {
            b[i] = a[p_right];
            p_right++;
        } else if ( (p_left < awe) && (p_right >= right) ) {
            b[i] = a[p_left];
            p_left++;
        } else if (a[p_left] > a[p_right]) {
            b[i] = a[p_right];
            p_right++;
        } else {
            b[i] = a[p_left];
            p_left++;
        }
    }

    for (size_t i = 0; i < right-left; i++) {
        a[i+left] = b[i];
    }

    return number_of_inversions;
}


void test_run(vector<int64_t> a, uint64_t correct) {
    std::cout << "Vector of " << a.size() << " : [";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size()-1) std::cout << ", ";
    }
    std::cout << "]...\n";

    int64_t answer = get_number_of_inversions(a, 0, a.size());
    
    std::cout << "Result of " << a.size() << " : [";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size()-1) std::cout << ", ";
    }
    std::cout << "]...\n";

    std::cout << "\tComparing " << answer << " == " << correct << "\n";

    assert( answer == correct );
    std::cout << "OK\n\n";
}

void test_solution(int64_t edje) {
    test_run(vector<int64_t>({ 3, 2, 1 }), 3);
    test_run(vector<int64_t>({ 2, 3, 9, 2, 9 }), 2);
    test_run(vector<int64_t>({ 9, 8, 7 }), 3);
    test_run(vector<int64_t>({ 9, 8, 7, 6 }), 6);
    test_run(vector<int64_t>({ 9, 8, 7, 3, 2, 1 }), 15);
}

void proceed() {
    uint64_t n;
    std::cin >> n;
    vector<int64_t> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << get_number_of_inversions(a, 0, a.size()) << '\n';
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        test_solution(10);
    } else if (argc == 3 && strcmp(argv[1], "--stress") == 0 ) {
        uint32_t edje = std::stoi(argv[2]);
        test_solution(edje);
    } else {
        proceed();
    }
    return 0;
}
