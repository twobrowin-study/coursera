#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdlib.h>

uint64_t MaxPairwiseProductReference(const std::vector<uint64_t>& numbers) {
    uint64_t max_product = 0;
    uint32_t n = numbers.size();

    for (uint32_t first = 0; first < n; ++first) {
        for (uint32_t second = first + 1; second < n; ++second) {
            uint64_t product = numbers[first] * numbers[second];
            max_product = std::max(max_product, product);
        }
    }

    return max_product;
}

uint64_t MaxPairwiseProduct(const std::vector<uint64_t>& numbers) {
    uint32_t top_max_index = 0;
    uint32_t led_max_index = -1;
    uint32_t n = numbers.size();

    for (uint32_t i = 1; i < n; ++i) {
        if (numbers[i] > numbers[top_max_index]) {
            top_max_index = i;
        }
    }

    for (uint32_t i = 0; i < n; ++i) {
        if ( (i != top_max_index) && ( (led_max_index == -1) || (numbers[i] > numbers[led_max_index]) ) ) {
            led_max_index = i;
        }
    }

    return numbers[top_max_index] * numbers[led_max_index];
}

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--stress") == 0 ) {
        while(true) {
            uint32_t n = rand() % 100 + 2;
            std::cout << n << std::endl;

            std::vector<uint64_t> numbers(n);
            for (uint32_t i = 0; i < n; ++i) {
                numbers[i] = rand() % 1000000;
                std::cout << numbers[i] << " ";
            }
            std::cout << std::endl;

            uint64_t result = MaxPairwiseProduct(numbers);
            uint64_t result_reference = MaxPairwiseProductReference(numbers);
            std::cout << result << " :: " << result_reference << " --> ";

            if (result == result_reference) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "ERR" << std::endl;
                return 1;
            }
        }
    } else {
        uint32_t n;
        std::cin >> n;
        std::vector<uint64_t> numbers(n);
        for (uint32_t i = 0; i < n; ++i) {
            std::cin >> numbers[i];
        }

        std::cout << MaxPairwiseProduct(numbers);
    }
    return 0;
}
