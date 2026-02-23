#include <bits/stdc++.h>

using namespace std;

const int INIT = -1;

// 프로토타입
bool isBipartiteFrom(const vector<vector<int>>&, vector<int>&, int, int);
bool isBipartiteGraph(const vector<vector<int>>&, int, int);
    
int main() {
    int K;
    cin >> K;

    while (K-- > 0) {
        int V, E;
        cin >> V >> E;

        vector<vector<int>> graph(V + 1, vector<int>());

        // 간선 정보 저장
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        if (isBipartiteGraph(graph, V, E)) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
    
    return 0;
}

// 깊이 우선 탐색으로 인접한 정점을 다른 색으로 색칠
bool isBipartiteFrom(const vector<vector<int>>& graph, vector<int>& colors, int curr, int color) {
    colors[curr] = color;

    for (int next : graph[curr]) {
        if (colors[next] == INIT) {
            if (!isBipartiteFrom(graph, colors, next, 1 - color)) {
                return false;
            }
        } else if (colors[next] == color) { // 인접한 두 정점이 같은 색이면 이분 그래프가 아님
            return false;
        }
    }

    return true;
}

// 현재 graph가 이분 그래프인지 확인
bool isBipartiteGraph(const vector<vector<int>>& graph, int V, int E) {
    vector<int> colors(V + 1, INIT);

    for (int v = 1; v <= V; v++) {
        if (colors[v] == INIT) {
            if (!isBipartiteFrom(graph, colors, v, 0)) {
                return false;
            }
        }
    }

    return true;
}