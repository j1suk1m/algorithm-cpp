#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;

    cin >> N >> K;

    vector<vector<int>> T(N, vector<int>(N));

    // 행성 간 이동 시간 저장
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> T[i][j];
        }
    }

    // 행성 간 최소 이동 시간 갱신
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j || j == k || k == i) continue;

                // i번째 행성에서 j번째 행성으로 이동할 때,
                // k번째 행성을 경유하는 것이 최소 이동 시간인 경우 갱신
                if (T[i][j] > T[i][k] + T[k][j]) {
                    T[i][j] = T[i][k] + T[k][j];
                }
            }
        }
    }

    const int INF = (int)1e5;
    vector<vector<int>> dp(1 << N, vector<int>(N, INF));

    // 출발 행성 상태 초기화
    dp[1 << K][K] = 0;

    // 비트마스크 DP를 통해 모든 방문 상태를 순회하면서
    // 현재까지 방문한 행성(i)에서 아직 방문하지 않은 행성(j)으로 이동하며
    // 방문 순서를 점진적으로 확장
    for (int mask = 0; mask < (1 << N); mask++) {
        for (int i = 0; i < N; i++) { // 현재 위치한 행성
            if (!(mask & (1 << i))) continue; // 방문한 상태가 아니면 skip
            if (dp[mask][i] == INF) continue; // 아직 도달한 적이 없으면 skip

            for (int j = 0; j < N; j++) { // 아직 방문하지 않은 행성
                if (mask & (1 << j)) continue; // 방문한 상태면 skip
                
                int nextMask = mask | (1 << j);
                dp[nextMask][j] = min(dp[nextMask][j], dp[mask][i] + T[i][j]);
            }
        }
    }

    int answer = INF;
    int fullMask = (1 << N) - 1; // 모든 행성을 방문한 상태

    // 가능한 모든 종료 위치 i에 대해 최솟값 갱신
    for (int i = 0; i < N; i++) {
        answer = min(answer, dp[fullMask][i]);
    }

    cout << answer;
    
    return 0;
}