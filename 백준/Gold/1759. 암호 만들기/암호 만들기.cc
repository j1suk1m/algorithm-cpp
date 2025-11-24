#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ALPHABET_COUNT = 26;

int L, C;
vector<char> temp; // 현재 조합 시도 중인 암호
vector<string> answer; // 최종 선택된 암호 목록

// ch가 모음인지 확인
bool isVowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

// temp가 유효한 암호인지 확인
bool isValid(const vector<char>& temp) {
    int vowelCount = 0;
    
    for (char ch : temp) {
        if (isVowel(ch)) {
            vowelCount++;
        }
    }

    // 모음이 한 개 이상, 자음이 두 개 이상인지 확인
    return vowelCount >= 1 && L - vowelCount >= 2;
}

// 백트래킹으로 알파벳 조합 계산
void backtrack(int startIndex, vector<char>& temp, const vector<char>& candidates) {
    if ((int)temp.size() == L) {
        if (isValid(temp)) {
            answer.emplace_back(temp.begin(), temp.end());       
        }
        
        return;
    }

    for (int i = startIndex; i < (int)candidates.size(); i++) {
        temp.push_back(candidates[i]);
        backtrack(i + 1, temp, candidates);
        temp.pop_back();
    }
}

int main() {
    cin >> L >> C;

    vector<char> candidates(C);

    for (int i = 0; i < C; i++) {
        cin >> candidates[i];
    }

    sort(candidates.begin(), candidates.end());
    
    backtrack(0, temp, candidates);

    for (string s : answer) {
        cout << s << "\n";
    }
    
    return 0;
}