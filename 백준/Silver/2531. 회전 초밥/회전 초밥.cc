#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, d, k, c;
    cin >> N >> d >> k >> c;

    vector<int> belt(N);

    // 회전 초밥 벨트 상태 저장
    for (int i = 0; i < N; i++) {
        int sushi;
        cin >> sushi;
        belt[i] = sushi;
    }

    // 구간별 초밥 등장 횟수
    vector<int> count(d + 1);

    int left = 0; // 왼쪽 포인터
    int right = k - 1; // 오른쪽 포인터
    int answer = 0; // 먹을 수 있는 최대 초밥 가짓수
    int distinct = 0; // 현재까지 먹은 초밥 가짓수

    // 초기 상태 저장
    for (int i = left; i <= right; i++) {
        count[belt[i]]++;

        // 서로 다른 초밥 가짓수 갱신
        if (count[belt[i]] == 1) {
            distinct++;
        }
    }

    for (int i = 0; i < N; i++) {
        // 최대 초밥 가짓수 갱신
        answer = max(
            answer, 
            distinct + (count[c] == 0 ? 1 : 0) // 현재 구간에 쿠폰 초밥이 없는 경우 가짓수 + 1        
        );
      
        if (count[belt[left]] == 1) {
            distinct--;
        }

        count[belt[left]]--;
        left++;

        right++;
        count[belt[right % N]]++;
        
        if (count[belt[right % N]] == 1) {
            distinct++;
        }
    }

    cout << answer;
    
    return 0;
}