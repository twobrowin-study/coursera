#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct Query {
    string type, name;
    size_t number;
};

vector<Query> read_queries() {
    size_t n;
    cin >> n;
    vector<Query> queries(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add") {
            cin >> queries[i].number >> queries[i].name;
        } else {
            cin >> queries[i].number;
        }
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<string> contacts(10000000, "");
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add")  {
            contacts[queries[i].number] = queries[i].name;
        } else  if (queries[i].type == "del")  {
            contacts[queries[i].number] = "";
        } else  if (queries[i].type == "find") {
            string response = "not found";
            if (contacts[queries[i].number] != "") {
                response = contacts[queries[i].number];
            }
            result.push_back(response);
        }
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
