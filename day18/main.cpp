#include <iostream>
#include <cstdint>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <cctype>
#include <unordered_map>
#include <deque>

class Item {
public:
    Item(char value, uint64_t precedence = 0) : token(value), precedence(precedence) {};

    bool is_value() const {
        return std::isdigit(token);
    }

    uint64_t get_value() const {
        return token - '0';
    }

    char get_token() const {
        return token;
    }

    bool operator != (const char other) const {
        return token != other;
    }

    bool operator < (const Item &other) const {
        return precedence < other.precedence;
    }

private:
    char token;
    uint64_t precedence;
};

const std::vector<std::string> read_stdin() {
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line)) {
        input.push_back(line);
    }
    return input;
}

bool pop_from_operator_stack(std::stack<Item> &operator_stack, Item op) {
    if (operator_stack.empty() || operator_stack.top().get_token() == '(') {
        return false;
    }
    if (operator_stack.top() < op) {
        return false;
    }
    return true;
}

void print_postfix_notation(const std::deque<Item> &stack) {
    for (auto c : stack) {
        std::cout << c.get_token();
    }
    std::cout << std::endl;
}

uint64_t evaluate(std::deque<Item> &&postfix_stack) {
    //print_postfix_notation(postfix_stack);
    std::stack<uint64_t> output;
    while(!postfix_stack.empty()) {
        if (postfix_stack.front().is_value()) {
            output.push(postfix_stack.front().get_value());
        } else {
            char token = postfix_stack.front().get_token();
            uint64_t operand1 = output.top();
            output.pop();
            uint64_t operand2 = output.top();
            output.pop();
            if (token == '+') {
                output.push(operand2 + operand1);
            } else if (token == '*') {
                output.push(operand2 * operand1);
            } else {
                std::cout << "invalid token: " << token << std::endl;
                exit(1);
            }
        }
        postfix_stack.pop_front();
    }
    return output.top();
}

std::deque<Item> get_postfix_notation(std::unordered_map<char, uint64_t> &precedence_map, const std::string &line) {
    std::deque<Item> output;
    std::stack<Item> operator_stack;
    for (auto token : line) {
        if (token == ' ') {
            continue;
        }
        if (std::isdigit(token)) {
            output.emplace_back(token);
        } else if (token == '+' || token == '*') {
            Item temp(token, precedence_map[token]);
            while (pop_from_operator_stack(operator_stack, temp)) {
                output.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(temp);
        } else if (token == '(') {
            operator_stack.emplace(token);
        } else if (token == ')') {
            while (operator_stack.top() != '(') {
                output.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.pop();
        } else {
            std::cout << "invalid token: " << token << std::endl;
            exit(1);
        }
    }
    while (!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }
    return output;
}

uint64_t first_solution(const std::vector<std::string> &input) {
    std::unordered_map<char, uint64_t> precedence_map {
        {'+', 0},
        {'*', 0},
    };
    uint64_t result = 0;
    for (auto &line : input) {
        result += evaluate(get_postfix_notation(precedence_map, line));
    }
    return result;
}

uint64_t second_solution(const std::vector<std::string> &input) {
    std::unordered_map<char, uint64_t> precedence_map {
        {'+', 1},
        {'*', 0},
    };
    uint64_t result = 0;
    for (auto &line : input) {
        result += evaluate(get_postfix_notation(precedence_map, line));
    }
    return result;
}

int main() {
    std::unordered_map<char, uint64_t> precedence_map {
        {'+', 1},
        {'*', 0},
    };
    assert(evaluate(get_postfix_notation(precedence_map, "2 * 3 + (4 * 5)")) == 46);

    const std::vector<std::string> input = read_stdin();
    uint64_t first = first_solution(input);
    uint64_t second = second_solution(input);
    std::cout << "first answer: " << first << std::endl;
    std::cout << "second answer: " << second << std::endl;
    assert(first == 14208061823964 && "first solution doesn't match");
    assert(second == 320536571743074 && "second solution doesn't match");
    return 0;
}
