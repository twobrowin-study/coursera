#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, long long position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    long long position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (long long position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push({ next, position });
        }

        if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                Bracket prev = opening_brackets_stack.top();
                opening_brackets_stack.pop();
                if (!prev.Matchc(next)) {
                    std::cout << position+1 << "\n";
                    return 1;
                }
            } else {
                std::cout << position+1 << "\n";
                return 1;
            }
        }
    }

    if (opening_brackets_stack.empty()) {
        std::cout << "Success\n";
    } else {
        Bracket first = {'/', -1};
        while(!opening_brackets_stack.empty()) {
            first = opening_brackets_stack.top();
            opening_brackets_stack.pop();
        }
        std::cout << first.position+1 << "\n";
        return 1;
    }

    return 0;
}
