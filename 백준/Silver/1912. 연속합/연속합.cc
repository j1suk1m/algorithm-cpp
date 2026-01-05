#include <bits/stdc++.h>

using namespace std;

const int MIN = -1000;

int main() {
    int n, element;
    vector<int> sequence;
    
    cin >> n;

    // 수열 저장
    for (int i = 0; i < n; i++) {
        cin >> element;
        sequence.push_back(element);
    }

    vector<int> table(n);

    // 기저 조건
    table[0] = sequence[0];

    // 다이나믹 프로그래밍
    for (int i = 1; i < n; i++) {
        table[i] = max(sequence[i], table[i - 1] + sequence[i]);
    }

    int answer = MIN * n - 1;

    // 최댓값 찾기
    for (int element : table) {
        answer = max(answer, element);    
    }

    cout << answer;

    return 0;
}