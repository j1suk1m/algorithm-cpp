#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> A(N);

    // 수열 저장
    for (int i = 0; i < N; i++) {
        int number;
        cin >> number;
        A[i] = number;
    }

    int left = 0; // 왼쪽 인덱스
    int right = 0; // 오른쪽 인덱스
    int sum = A[left]; // 구간의 합 // A[left] + ... A[right]
    int answer = 0; // 경우의 수

    // 투 포인터 알고리즘 수행
    while (right < N) {
        if (sum == M) { // 현재 구간의 합이 타겟과 같은 경우
            answer++; // 경우의 수 증가
            sum -= A[left];
            left++;
        } else if (sum < M) { // 현재 구간의 합이 타겟보다 작은 경우
            if (right >= N - 1) break;
            right++; // 구간 증가
            sum += A[right]; 
        } else { // 현재 구간의 합이 타겟보다 큰 경우
            sum -= A[left]; 
            left++; // 구간 감소
        }
    }

    cout << answer;
    
    return 0;
}