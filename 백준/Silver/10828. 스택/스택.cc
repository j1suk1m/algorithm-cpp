#include <iostream>
#include <string>
#include <stack>

using namespace std;

const string NEW_LINE = "\n";
const string PUSH = "push";
const string POP = "pop";
const string SIZE = "size";
const string EMPTY = "empty";
const string TOP = "top";
const string ERROR = "-1";
const string IS_EMPTY = "1";
const string IS_NOT_EMPTY = "0";
stack<int> s;

int main() {
    // 입출력 최적화 세팅
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, value;
    string command, answer;

    cin >> N;

    // 스택 명령 수행
    while (N-- > 0) {
        cin >> command;

        if (command == PUSH) { // push 연산
            cin >> value;
            s.push(value);
            continue;
        } else if (command == POP) { // pop 연산
            if (s.empty()) {
                answer += ERROR;
            } else {
                answer += to_string(s.top());
                s.pop();
            }
        } else if (command == SIZE) { // size 연산
            answer += to_string(s.size());
        } else if (command == EMPTY) { // empty 연산
            answer += (s.empty() ? IS_EMPTY : IS_NOT_EMPTY);
        } else if (command == TOP) { // top 연산
            if (s.empty()) {
                answer += ERROR;
            } else {
                answer += to_string(s.top());
            }            
        }
        
        // 그 외 연산 무시

        answer += NEW_LINE;
    }

    cout << answer;
    
    return 0;
}