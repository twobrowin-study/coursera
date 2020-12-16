#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;
using std::cin;
using std::cout;

class JobQueue {
 private:
    size_t num_workers_;
    vector<uint32_t> jobs_;

    vector<uint32_t> assigned_workers_;
    vector<uint64_t> start_times_;

    void WriteResponse() const {
        for (size_t i = 0; i < jobs_.size(); i++) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        size_t m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (size_t i = 0; i < m; i++) {
            cin >> jobs_[i];
        }
    }

protected:
    struct worker {
        size_t   idx;
        uint64_t time;
        inline friend bool operator< (const worker& lhs, const worker& rhs) {
            if (lhs.time < rhs.time) return true;
            if (lhs.time == rhs.time && lhs.idx < rhs.idx) return true;
            return false;
        }
    };
    vector<worker> wheap_;

    void AssignJobs() {
        for (size_t i = 0; i < num_workers_; i++) {
            wheap_.push_back({i, 0});
        }
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());

        for (size_t i = 0; i < jobs_.size(); i++) {
            worker toper = wheap_[0];
            start_times_[i] = toper.time;
            assigned_workers_[i] = toper.idx;
            wheap_[0] = {toper.idx, toper.time + jobs_[i]};
            ShiftDown(0);
        }
    }

    inline size_t Lchild(size_t idx) { return 2*idx + 1; }
    inline size_t Rchild(size_t idx) { return 2*idx + 2; }

    void ShiftDown(size_t idx) {
        size_t min_idx = idx;

        size_t l_idx = Lchild(idx);
        if (l_idx < wheap_.size() && wheap_[l_idx] < wheap_[min_idx]) {
            min_idx = l_idx;
        }
        
        size_t r_idx = Rchild(idx);
        if (r_idx < wheap_.size() && wheap_[r_idx] < wheap_[min_idx]) {
            min_idx = r_idx;
        }

        if (min_idx != idx) {
            swap(wheap_[idx], wheap_[min_idx]);
            ShiftDown(min_idx);
        }
    }

 public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
