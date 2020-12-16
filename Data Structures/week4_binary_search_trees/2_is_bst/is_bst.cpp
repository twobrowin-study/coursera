#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

struct Node {
    int32_t key;
    int32_t left;
    int32_t right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int32_t key_, int32_t left_, int32_t right_) : key(key_), left(left_), right(right_) {}
};

struct Search {
    int32_t index;
    int32_t min;
    int32_t max;
    bool    is_left;
};

bool IsBinarySearchTree(const vector<Node>& tree) {
    queue<Search> branch;
    branch.push({0, INT_MIN, INT_MAX, false});
    while(!branch.empty()) {
        Search srch = branch.front();
        Node node = tree[srch.index];
        branch.pop();
        if ((srch.min > node.key) || (node.key > srch.max) || (srch.is_left && node.key == srch.max))
            return false;
        if (node.left != -1)
            branch.push({node.left,  srch.min, node.key, true});
        if (node.right != -1)
            branch.push({node.right, node.key, srch.max, false});
    }
    return true;
}

int main() {
    int32_t nodes;
    cin >> nodes;
    vector<Node> tree(nodes);
    for (int32_t i = 0; i < nodes; ++i) {
        int32_t key, left, right;
        cin >> key >> left >> right;
        tree[i] = Node(key, left, right);
    }
    if (nodes == 0 || IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
