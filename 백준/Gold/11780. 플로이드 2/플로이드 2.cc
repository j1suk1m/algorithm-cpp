#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;

int main() {
    // 빠른 입출력 설정
    ios_base:: sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int a, b, c;

    // cost[i][j]: i -> j 최소 비용
    // path[i][j]: i -> j 최단 경로
    vector<vector<int>> cost(n + 1, vector<int>(n + 1, INF));
    vector<vector<vector<int>>> path(n + 1, vector<vector<int>>(n + 1));

    // 자기 자신으로 가는 경로를 기준 상태로 설정
    for (int v = 1; v <= n; v++) {
        cost[v][v] = 0;
        path[v][v] = {v};
    }

    // 직접 연결된 간선 정보로 초기 그래프 구성
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        cost[a][b] = min(cost[a][b], c); // 여러 간선 중 최소 비용만 유지
        path[a][b] = {a, b};
    }

    // k를 경유지 집합에 하나씩 추가하면서
    // i -> j 최단 경로를 점진적으로 확장
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // k를 경유하는 것이 최소 비용이라면 갱신
                if (cost[i][j] > cost[i][k] + cost[k][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];

                    // 기존 i -> k 경로 뒤에
                    // k -> j 경로를 이어붙여 전체 경로 구성
                    path[i][j] = path[i][k];
                    path[i][j].insert(
                        path[i][j].end(),
                        path[k][j].begin() + 1, // k가 중복이므로 제거
                        path[k][j].end()
                    );
                }
            }
        }
    }

    ostringstream oss;

    // 모든 도시 쌍 (i, j)에 대한 최소 비용 출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (cost[i][j] == INF) { // 도달 불가능한 경우 0 출력
                oss << 0 << " ";
            } else {
                oss << cost[i][j] << " ";
            }
        }

        oss << "\n";
    }

    // 각 경로의 실제 방문 순서 출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || cost[i][j] == INF) { // 자기 자신이거나, 경로가 없는 경우 0 출력
                oss << 0 << "\n";
            } else {
                oss << path[i][j].size() << " ";

                for (int v : path[i][j]) {
                    oss << v << " ";
                }

                oss << "\n";
            }
        }
    }

    cout << oss.str();
    
    return 0;
}