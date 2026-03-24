#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    vector<int> minCost(N, INF);
    vector<bool> visited(N, false);

    int start = 0;
    minCost[start] = 0;

    long long answer = 0LL;

    for (int i = 0; i < N; i++) {
        // 최소 정점 선택
        int u = -1;
        int cost = INF;

        for (int j = 0; j < N; j++) {
            if (!visited[j] && minCost[j] < cost) {
                cost = minCost[j];
                u = j;
            }
        }

        // 최소 신장 트리에 최소 정점 포함
        visited[u] = true;
        answer += cost;

        // 인접 정점 가중치 갱신
        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] != 0) {
                minCost[v] = min(minCost[v], graph[u][v]);
            }
        }
    }

    cout << answer;
    
    return 0;
}