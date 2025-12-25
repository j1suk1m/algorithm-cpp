#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// number가 홀수인지 반환하는 함수
bool isOdd(int number) {
    return number % 2 == 1;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> S(N);

    // 수열 저장
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;
        S[i] = number;
    }

    int left = 0; // 왼쪽 포인터
    int answer = 0; // 짝수로만 이루어진 연속 부분 수열의 최대 길이
    int oddCount = 0; // 현재 구간(left ~ right)에 속한 홀수의 개수

    // 투 포인터 알고리즘 수행
    for (int right = 0; right < N; right++) {
        if (isOdd(S[right])) {
            // 현재 right 포인터가 가리키는 숫자가 홀수이므로,
            // 이 숫자를 제외하고 현재 구간에 속한 홀수의 개수가 K - 1이 되도록 left 포인터 증가
            while (oddCount >= K) {
                if (isOdd(S[left])) {
                    oddCount--;
                }

                left++;
            }

            oddCount++;
        }

        // 구간의 단순 길이 계산
        int intervalLength = right - left + 1;

        // 짝수로만 이루어진 연속 부분 수열의 최대 길이 갱신
        answer = max(answer, intervalLength - oddCount);
    }

    cout << answer;
    
    return 0;
}