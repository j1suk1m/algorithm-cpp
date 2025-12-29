#include <iostream>
#include <vector>

using namespace std;

const int MAX = (int)1e5;

int main() {
    int N;
    cin >> N;

    vector<int> sequence;
    int element;

    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> element;
        sequence.push_back(element);
    }
    
    int left = 0; // 왼쪽 포인터
    int right = 0; // 오른쪽 포인터
    long long answer = 0LL; // 경우의 수
    vector<int> count(MAX + 1); // 구간 [left, right]에 포함된 숫자별 등장 횟수

    // 투 포인터 알고리즘 수행
    while (right < N) {
        // 현재 right 포인터가 가리키는 숫자의 등장 횟수 증가
        count[sequence[right]]++;

        // 현재 right 포인터가 가리키는 숫자가 중복이 아닐 때까지 left 포인터 이동
        while (count[sequence[right]] > 1) {
            count[sequence[left]]--;
            left++;
        }

        // 중복 없는 구간 [left, right]에서 만들 수 있는 부분 수열의 개수 누적
        answer += right - left + 1;
        
        right++;
    }

    cout << answer;
    
    return 0;
}