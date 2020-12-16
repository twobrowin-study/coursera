#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <queue>

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::queue;

struct Node: std::enable_shared_from_this<Node> {
    void setParent(shared_ptr<Node> parent) {
        this->parent = parent;
        this->parent->children.push_back(shared_from_this());
    }

    shared_ptr<Node> parent;
    vector<shared_ptr<Node>> children;
};

int main(int argc, char *argv[]) {
    int32_t n;
    std::cin >> n;
    
    std::vector<shared_ptr<Node>> nodes;
    for (int32_t i; i < n; i++) {
        nodes.push_back(make_shared<Node>());
    }
    
    shared_ptr<Node> root;
    for (int32_t child_idx = 0; child_idx < n; child_idx++) {
        int32_t parent_idx;
        std::cin >> parent_idx;
        if (parent_idx >= 0) {
            nodes[child_idx]->setParent(nodes[parent_idx]);
        } else {
            root = nodes[child_idx];
        }
    }

    int32_t height = 0;
    queue<shared_ptr<Node>> edje;
    edje.push(root);
    while(!edje.empty()) {
        queue<shared_ptr<Node>> next_edje;
        
        while(!edje.empty()) {
            shared_ptr<Node> curr = edje.front();
            edje.pop();
            
            for (auto child : curr->children) {
                next_edje.push(child);
            }
        }
        
        edje.swap(next_edje);
        height++;
    }

    std::cout << height << std::endl;
    return 0;
}
