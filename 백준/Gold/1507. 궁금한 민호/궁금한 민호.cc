#include <bits/stdc++.h>

using namespace std;

// 프로토타입
int solve(int N, const vector<vector<int>>& cost);

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> cost[i][j];
        }
    }

    int answer = solve(N, cost);
    cout << answer;
    
    return 0;
}

int solve(int N, const vector<vector<int>>& cost) {
    int answer = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // i -> j 간선 필요 여부
            bool isNeeded = true;

            for (int k = 0; k < N; k++) {
                if (k == i || k == j) continue;

                // 모순이므로 즉시 종료
                if (cost[i][j] > cost[i][k] + cost[k][j]) {
                    return -1;
                }

                // i -> k, k -> j 간선이 존재하므로
                // i -> j 간선은 제거 가능
                if (cost[i][j] == cost[i][k] + cost[k][j]) {
                    isNeeded = false;
                }
            }

            if (isNeeded) {
                answer += cost[i][j];
            }
        }
    }

    return answer;
}