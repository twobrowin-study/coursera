#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>

using std::vector;
using std::stack;
using std::cin;
using std::cout;

void print(vector <int32_t> a);

class TreeOrders {
    size_t n;
    vector <int32_t> key;
    vector <int32_t> left;
    vector <int32_t> right;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (size_t i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }


    vector <int32_t> in_order() {
        vector<int32_t> result;
        stack<int32_t> branch;
        vector<bool> check(n, false);
        branch.push(0);
        while(!branch.empty()) {
            int32_t node = branch.top();
            if (left[node] != -1 && check[left[node]] == false) {
                branch.push(left[node]);
            }
            if ((left[node] == -1 || check[left[node]] == true)) {
                result.push_back(key[node]);
                check[node] = true;
                branch.pop();
                if (right[node] != -1 && check[right[node]] == false) {
                    branch.push(right[node]);
                }
            }
        }
        return result;
    }

    vector <int32_t> pre_order() {
        vector<int32_t> result;
        stack<int32_t> branch;
        branch.push(0);
        while(!branch.empty()) {
            int32_t node = branch.top();
            result.push_back(key[node]);
            branch.pop();
            if (right[node] != -1)
                branch.push(right[node]);
            if (left[node] != -1)
                branch.push(left[node]);
        }
        return result;
    }

    vector <int32_t> post_order() {
        vector<int32_t> result;
        vector<bool> check(n, false);
        stack<int32_t> branch;
        branch.push(0);
        while(!branch.empty()) {
            int32_t node = branch.top();
            if (right[node] != -1 && check[right[node]] == false) {
                branch.push(right[node]);
            }
            if (left[node] != -1 && check[left[node]] == false) {
                branch.push(left[node]);
            }
            if (( left[node] == -1 || check[ left[node]] == true) && 
                (right[node] == -1 || check[right[node]] == true)) {
                result.push_back(key[node]);
                check[node] = true;
                branch.pop();
            }
        }
        return result;
    }
};

void print(vector <int32_t> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << a[i];
    }
    cout << "\n";
}

int main() {
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}
