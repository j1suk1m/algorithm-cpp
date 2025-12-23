#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = (int) 1e5;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> a;

    // 수열 저장
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;
        a.push_back(number);
    }
    
    // count[x] = 현재 연속 부분 수열에서 x가 포함된 개수 
    vector<int> count(MAX + 1); 

    int left = 0; // 왼쪽 인덱스
    int answer = 0; // 경우의 수

    // 투 포인터 알고리즘 수행
    for (int right = 0; right < N; right++) {
        count[a[right]]++;

        // 현재 연속 부분 수열에 속한 모든 숫자가 K개 이하일 때까지 left 증가
        // count[a[left]] ~ count[a[right]]가 아니라 count[a[right]]만 평가하는 이유는 a[right]만 조건을 위반할 수 있기 때문
        while (count[a[right]] > K) {
            count[a[left]]--;
            left++;
        }

        // 최대 길이 갱신
        // right - left + 1 = 부분 수열의 길이
        answer = max(answer, right - left + 1);
    }

    cout << answer;
    
    return 0;
}