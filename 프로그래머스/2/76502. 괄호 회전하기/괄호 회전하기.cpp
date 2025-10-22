#include <string>
#include <stack>
#include <map>
#include <set>

using namespace std;

const map<char, char> brackets = {{')', '('}, {']', '['}, {'}', '{'}};
set<char> openingBrackets;

bool isOpeningBracket(char ch);
bool isValid(const string& s);
string rotate(string& s);

int solution(string s) {
    int answer = 0;
    
    for (const auto& [key, value] : brackets) {
        openingBrackets.insert(value);
    }
    
    for (int i = 0; i < (int)s.size(); i++) {
        if (isValid(s)) { // 괄호 유효성 검사
            answer++;
        }
        
        s = rotate(s); // 괄호 회전
    }
    
    return answer;
}

bool isOpeningBracket(char ch) {
    return openingBrackets.find(ch) != openingBrackets.end();
}

bool isValid(const string& s) {
    stack<char> bracketStack;
    
    for (int i = 0; i < (int)s.size(); i++) {
        char ch = s[i];
        
        if (isOpeningBracket(ch)) { // 여는 괄호인 경우
            bracketStack.push(ch);
        } else if (!bracketStack.empty() && brackets.at(ch) == bracketStack.top()) { // 닫는 괄호이고 짝이 맞는 경우
            bracketStack.pop();
        } else {
            return false;
        }
    }
    
    return bracketStack.empty();
}

string rotate(string& s) {
    return s.substr(1, (int)s.size() - 1) + s[0];
}