#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct Query {
    string type, s;
    size_t ind;
};

struct Chain {
    Chain(string content) {
        this->content = content;
        this->next = nullptr;
    }

    string content;
    shared_ptr<Chain> next;
};

class QueryProcessor {
private:
    uint64_t bucket_count;
    vector<shared_ptr<Chain>> hash_map;

protected:
    uint64_t hash_func(const string& s) const {
        static const uint64_t multiplier = 263;
        static const uint64_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int64_t i = static_cast<int64_t> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(uint64_t bucket_count): bucket_count(bucket_count), hash_map(bucket_count, nullptr) {
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes" : "no") << endl;
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            for (shared_ptr<Chain> ch = hash_map[query.ind]; ch != nullptr; ch = ch->next) {
                cout << ch->content << " ";
            }
            cout << endl;
        } else {
            uint64_t hash = hash_func(query.s);
            shared_ptr<Chain> ch = hash_map[hash];
            if (query.type == "add") {
                bool was_found = false;
                shared_ptr<Chain> tmp = ch;
                while (ch != nullptr) {
                    if (ch->content == query.s) {
                        was_found = true;
                        break;
                    }
                    ch = ch->next;
                }
                if (was_found == false) {
                    hash_map[hash] = make_shared<Chain>(query.s);
                    hash_map[hash]->next = tmp;
                }
            } else if (query.type == "find") {
                bool was_found = false;
                while (ch != nullptr) {
                    if (ch->content == query.s) {
                        was_found = true;
                        break;
                    }
                    ch = ch->next;
                }
                writeSearchResult(was_found);
            } else if (query.type == "del") {
                if (ch != nullptr) {
                    shared_ptr<Chain> prev = nullptr;
                    while (ch != nullptr) {
                        if (ch->content == query.s) {
                            break;
                        }
                        prev = ch;
                        ch = ch->next;
                    }
                    if (ch != nullptr && prev == nullptr) {
                        hash_map[hash] = ch->next;
                    }
                    if (ch != nullptr && prev != nullptr) {
                        prev->next = ch->next;
                    }
                }
            }
        }
    }

    void processQueries() {
        size_t n;
        cin >> n;
        for (size_t i = 0; i < n; ++i) {
            processQuery(readQuery());
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    size_t bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
