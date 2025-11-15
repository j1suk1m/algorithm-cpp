#include <iostream>
#include <vector>

using namespace std;

const int END = 0;
const int MAX_COUNT = 6;

/**
    백트래킹으로 로또 번호 조합을 구하는 함수
    
    count: 현재까지 선택한 로또 번호 개수
    start: 로또 번호 집합 S에서의 인덱스
    totalCount: 로또 번호 집합 S 크기
    S: 로또 번호 집합
    combination: 현재까지 선택한 로또 번호 조합
*/
void backtrack(int count, int start, int totalCount, const vector<int>& S, vector<int>& combination) {
    if (count == MAX_COUNT) {
        for (const int element : combination) {
            cout << element << " ";
        }

        cout << "\n";
        return;
    }

    for (int i = start; i < totalCount; i++) {
        combination.push_back(S[i]);
        backtrack(count + 1, i + 1, totalCount, S, combination);
        combination.pop_back();
    }
}

int main() {
    int k;

    while (cin >> k && k != END) {
        vector<int> S(k);
        vector<int> combination;

        // 집합 저장
        for (int i = 0; i < k; i++) {
            cin >> S[i];
        }

        // 백트래킹 실행
        backtrack(0, 0, k, S, combination);
        cout << "\n";
    }
    
    return 0;
}