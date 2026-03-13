#include <bits/stdc++.h>

using namespace std;

// 경로가 존재하지 않을 때를 나타내는 충분히 큰 값
const int INF = (int)1e9; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    // changeCount[i][j]:
    // i -> j로 이동하기 위해 양방향 도로로 변경해야 하는 최소 횟수
    // 초기에는 경로가 없다고 가정하고 INF로 설정
    vector<vector<int>> changeCount(n + 1, vector<int>(n + 1, INF));

    // 자기 자신으로 이동하는 경우, 도로 변경 불필요
    for (int i = 1; i <= n; i++) {
        changeCount[i][i] = 0;
    }
    
    for (int i = 0; i < m; i++) {
        int u, v, b;
        cin >> u >> v >> b;

        // u -> v 는 항상 존재
        changeCount[u][v] = 0;

        // b == 0: u -> v 단방향
        // b == 1: 양방향
        //
        // v -> u로 이동하기 위해서는
        // 1) 단방향이면 양방향 도로로 변경 필요(1)
        // 2) 양방향이면 그대로 이동 가능(0)
        //
        // 따라서 b의 값을 토글한 것과 동일
        changeCount[v][u] = 1 - b; 
    }

    // 플로이드 워셜 알고리즘
    // 모든 정점 쌍 (i, j)에 대해
    // 중간 정점 k를 경유하는 것이 도로 변경 횟수를 줄일 수 있는지 확인
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                changeCount[i][j] = min(
                    changeCount[i][j], 
                    changeCount[i][k] + changeCount[k][j]
                );
            }
        }
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        cout << changeCount[u][v] << "\n";
    }
    
    return 0;
}