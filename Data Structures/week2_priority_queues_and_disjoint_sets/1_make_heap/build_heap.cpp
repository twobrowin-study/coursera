#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<uint32_t> data_;
    vector<pair<size_t, size_t>> swaps_;

    void write_response() const {
        cout << swaps_.size() << endl;
        for (size_t i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << endl;
        }
    }

    void read_data() {
        size_t n;
        cin >> n;
        data_.resize(n);
        for(size_t i = 0; i < n; ++i)
            cin >> data_[i];
    }

protected:
    void generate_swaps() {
        for (int32_t i = parent(data_.size()-1); i >= 0; i--) {
            shift_down(i);
        }
    }

    inline size_t parent(size_t idx) { return (idx-1)/2; }
    inline size_t lchild(size_t idx) { return 2*idx + 1; }
    inline size_t rchild(size_t idx) { return 2*idx + 2; }

    void shift_down(size_t idx) {
        size_t min_idx = idx;

        size_t l_idx = lchild(idx);
        if (l_idx < data_.size() && data_[l_idx] < data_[min_idx]) {
            min_idx = l_idx;
        }
        
        size_t r_idx = rchild(idx);
        if (r_idx < data_.size() && data_[r_idx] < data_[min_idx]) {
            min_idx = r_idx;
            }
            
        if (min_idx != idx) {
            swap(data_[idx], data_[min_idx]);
            swaps_.push_back(make_pair(idx, min_idx));
            shift_down(min_idx);
        }
    }

public:
    void solve() {
        read_data();
        generate_swaps();
        write_response();
    }
};

int main() {
    HeapBuilder heap_builder;
    heap_builder.solve();
    return 0;
}
