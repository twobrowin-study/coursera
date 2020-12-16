#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &array) {
    int i, majorityIndex = 0, count = 1;
    int size = array.size();
    for(i = 1; i < size; i++) {
        if(array[majorityIndex] == array[i])
            count++;
        else
            count--;
         
        if(count == 0) {
            majorityIndex = i;
            count = 1;
        }
    }
    count = 0;
    for (i = 0; i < size; i++) {
        if(array[i] == array[majorityIndex])
            count++;
    }
    if(count > (size/2)) return array[majorityIndex];
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a) != -1) << '\n';
}
