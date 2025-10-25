#include <iostream>
#include <stack>
#include <map>

using namespace std;

// key: 연산자 또는 여는 괄호, value: 우선순위
map<char, int> priorities = {{'(', 1}, {'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}};

// 프로토타입
bool isCapitalLetter(char ch);
bool hasEqualOrHigherPriority(char ch1, char ch2);

int main() {
    string infix, postfix;
    stack<char> s;

    // 중위 표기식 입력
    cin >> infix;

    for (int i = 0; i < (int)infix.size(); i++) {
        char curr = infix[i];

        if (isCapitalLetter(curr)) { // 피연산자인 경우 -> 후위 표기식에 바로 추가
            postfix.push_back(curr);
        } else if (curr == '(') { // 여는 괄호인 경우 -> 스택에 push
            s.push(curr);
        } else if (curr == ')') { // 닫는 괄호인 경우 -> 여는 괄호가 나올 때까지 pop
            char top = s.top(); s.pop();
            
            while (top != '(') {
                postfix.push_back(top);
                top = s.top(); s.pop();
            }
        } else { // 연산자인 경우 -> 스택이 비거나 최상단에 우선순위가 낮은 연산자가 올 때까지 pop + 스택에 push            
            while (!s.empty() && hasEqualOrHigherPriority(s.top(), curr)) {
                postfix.push_back(s.top());
                s.pop();
            }

            s.push(curr);
        }
    }

    // 스택에 남은 연산자를 후위 표기식에 추가
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }

    // 후위 표기식 출력
    cout << postfix;

    return 0;
}

// 알파벳 대문자(피연산자) 여부 반환
bool isCapitalLetter(char ch) {
    return 'A' <= ch && ch <= 'Z';
}

// ch1이 ch2보다 크거나 같은 우선순위를 갖는지 여부 반환
bool hasEqualOrHigherPriority(char ch1, char ch2) {
    return priorities[ch1] >= priorities[ch2];
}