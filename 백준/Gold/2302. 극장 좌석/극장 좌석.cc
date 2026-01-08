#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> vip(M);

    // VIP 고정석 번호 저장
    for (int i = 0; i < M; i++) {
        cin >> vip[i];
    }

    vector<int> fibonacci(N + 1);

    // 기저 조건
    fibonacci[0] = 1;
    fibonacci[1] = 1;

    // 피보나치 수열 생성
    for (int i = 2; i <= N; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }
    
    int start = 1;
    int answer = 1;

    for (int i = 0; i < M; i++) {
        int end = vip[i] - 1;
        answer *= fibonacci[end - start + 1]; // [start ~ end]는 일반석으로만 구성된 구간
        start = vip[i] + 1;
    }

    // 마지막 구간 처리
    if (start < N) {
        answer *= fibonacci[N - start + 1];
    }

    cout << answer;

    return 0;
}