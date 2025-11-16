#include <iostream>
#include <vector>

using namespace std;

int answer;
int N, S;
vector<int> sequence(20);

/**
    백트래킹으로 합이 S가 되는 부분 수열의 개수를 구하는 함수

    start: 수열 sequence에서의 인덱스
    count: 현재까지 선택한 숫자의 개수
    total: 최종적으로 선택할 전체 숫자의 개수
    result: 현재까지 계산한 부분 수열의 합
*/
void backtrack(int start, int count, int total, int result) {
    if (count == total && result == S) {
        answer++;
        return;
    }

    for (int i = start; i < N; i++) {
        backtrack(i + 1, count + 1, total, result + sequence[i]);
    }
}

int main() {
    cin >> N >> S;
    
    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    // 백트래킹 실행
    for (int total = 1; total <= N; total++) {
        backtrack(0, 0, total, 0);
    }

    cout << answer;
    
    return 0;
}