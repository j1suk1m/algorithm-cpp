#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));

    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
    }

    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= V; i++) {
            for (int j = 1; j <= V; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int minDist = INF;

    for (int i = 1; i <= V; i++) {
        minDist = min(minDist, dist[i][i]); // i -> i 사이클
    }

    if (minDist == INF) {
        cout << -1;
    } else {
        cout << minDist;
    }
    
    return 0;
}