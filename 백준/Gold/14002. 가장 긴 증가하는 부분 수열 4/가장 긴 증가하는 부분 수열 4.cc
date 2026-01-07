#include <bits/stdc++.h>

using namespace std;

const int NONE = -1;

int main() {
    int N;
    cin >> N;

    vector<int> sequence(N);

    // 수열 저장
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    vector<int> length(N, 1);
    vector<int> parents(N, NONE); // 정답 수열에서 바로 이전 원소의 인덱스 // 역추적에 사용

    // 다이나믹 프로그래밍
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (sequence[i] > sequence[j] && length[i] < length[j] + 1) {
                length[i] = length[j] + 1;
                parents[i] = j;
            }
        }
    }

    int lastIndex = 0;
    int maxLength = 0;
    
    // 최대 길이 찾기
    for (int i = 0; i < N; i++) {
        if (maxLength < length[i]) {
            maxLength = length[i];
            lastIndex = i;
        }
    }

    int curr = lastIndex;
    vector<int> answer;
    
    // 역추적
    while (curr != NONE) {
        answer.push_back(sequence[curr]);
        curr = parents[curr];
    }
    
    reverse(answer.begin(), answer.end());

    cout << maxLength << "\n";

    for (int element : answer) {
        cout << element << " ";
    }
    
    return 0;
}