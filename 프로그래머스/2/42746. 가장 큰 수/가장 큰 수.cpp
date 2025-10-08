#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isAllZero(vector<int>&);

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> numberStrings;
    
    // 모두 0인 경우 early return
    // 이때 처리하지 않으면 "000..0"이 반환될 수 있음
    if (isAllZero(numbers)) {
        return "0";
    }
    
    // vector<int> -> vector<string> 변환
    for (int number : numbers) {
        numberStrings.push_back(to_string(number));
    }
    
    // 정수를 이어 붙여서 더 큰 수를 만들 수 있는 순서대로 정렬
    sort(numberStrings.begin(), numberStrings.end(), [](const string& s1, const string& s2) {
        return stoi(s1 + s2) > stoi(s2 + s1);
    });
    
    for (string str : numberStrings) {
        answer += str;
    }
    
    return answer;
}

// numbers의 모든 요소가 0인지 확인
bool isAllZero(vector<int>& numbers) {
    for (int number : numbers) {
        if (number != 0) {
            return false;
        }
    }
    
    return true;
}