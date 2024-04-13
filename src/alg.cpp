#include <string>
#include <map>
#include "tstack.h"
std::map<char, int> priority {
        {'(', 0}, {')', 1}, {'-', 2}, {'+', 2}, {'*', 3}, {'/', 3}
};
TStack<char, 100> stack1;
TStack<int, 100> stack2;
std::string infx2pstfx(std::string inf) {
    std::string c = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            c += inf[i];
            c += ' ';
        } else {

            if (inf[i] == '(' || stack1.isEmpty() == 1 ||
            priority[inf[i]] > priority[stack1.get()]) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    c = c + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (priority[inf[i]] <= priority[stack1.get()]) {
                char item = stack1.pop();
                c = c + item + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        c = c + stack1.pop();
        if (stack1.isEmpty() != 1) {
            c += ' ';
        }
    }
    return c;
}
int eval(std::string pref) {
    std::string str;
    char cPerem;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            str += i;
        } else if (!str.empty() && i == ' ') {
            stack2.push(std::stoi(str));
            str.clear();
        } else {
            switch (i) {
                case '-': {
                    cPerem = stack2.pop();
                    stack2.push(stack2.pop() - cPerem);
                    break;
                }
                case '/': {
                    cPerem = stack2.pop();
                    stack2.push(stack2.pop() / cPerem);
                    break;
                }
                case '+': {
                    cPerem = stack2.pop();
                    stack2.push(stack2.pop() + cPerem);
                    break;
                }
                case '*': {
                    cPerem = stack2.pop();
                    stack2.push(stack2.pop() * cPerem);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
