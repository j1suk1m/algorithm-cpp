#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;
const int CANNOT_GO = 0;

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> costs(N + 1, vector<int>(N + 1, INF));

    // 자기 자신으로 향하는 비용을 0으로 설정
    for (int i = 1; i <= N; i++) {
        costs[i][i] = 0;
    }

    // 버스 정보 저장
    for (int i = 0; i < M; i++) {
        int src, dest, cost;
        cin >> src >> dest >> cost;
        costs[src][dest] = min(costs[src][dest], cost); // 동일한 (src, dest)에 여러 노선 존재 가능
    }

    // 최소 비용 갱신
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == j || j == k || k == i) continue;

                if (costs[i][j] > costs[i][k] + costs[k][j]) {
                    costs[i][j] = costs[i][k] + costs[k][j];
                }
            }
        }
    }

    ostringstream oss;

    // 정답 문자열 생성
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++) {
            if (costs[i][j] == INF) {
                oss << CANNOT_GO << " ";
            } else {
                oss << costs[i][j] << " ";
            }
        }

        oss << "\n";
    }

    cout << oss.str();
    
    return 0;
}