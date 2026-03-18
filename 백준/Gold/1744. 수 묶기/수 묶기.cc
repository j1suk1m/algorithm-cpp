#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> sequence(N);

    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    // 수열 오름차순 정렬
    sort(sequence.begin(), sequence.end());

    int left = 0;
    int right = N - 1;
    int sum = 0;

    // 큰 수부터 두 개씩 묶기
    while (right > 0 && sequence[right - 1] > 1) { // 1은 곱하는 것보다 더하는 게 이득이므로 제외
        sum += sequence[right] * sequence[right - 1];
        right -= 2;
    }

    // 작은 수부터 두 개씩 묶기
    while (left < right && sequence[left] < 0 && sequence[left + 1] <= 0) {
        sum += sequence[left] * sequence[left + 1];
        left += 2;
    }

    // 남은 수 더하기
    while (left <= right) {
        sum += sequence[left];
        left++;
    }

    cout << sum;
    
    return 0;
}