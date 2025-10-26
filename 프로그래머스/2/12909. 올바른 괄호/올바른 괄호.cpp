#include <string>
#include <stack>

using namespace std;

bool solution(string s) {
    char openingBracket = '(';
    char closingBracket = ')';
    
    if (s[0] == closingBracket) return false;
    
    stack<char> brackets;
    
    for (int i = 0; i < (int)s.size(); i++) {
        char curr = s[i];
        
        if (curr == openingBracket) { // 여는 괄호인 경우 -> 스택에 push
            brackets.push(curr);
        } else { // 닫는 괄호인 경우 -> 스택의 top에 여는 괄호가 있는지 확인
            if (brackets.empty() || brackets.top() != openingBracket) {
                return false;
            }
            
            brackets.pop();
        }
    }
    
    // 스택이 비어 있지 않으면 올바르지 않은 괄호
    return brackets.empty();
}