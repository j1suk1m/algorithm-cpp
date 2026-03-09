#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;

int main() {
    int n, m, r;
    cin >> n >> m >> r;

    vector<int> itemCounts(n + 1); // 구역별 아이템 개수

    for (int i = 1; i <= n; i++) {
        cin >> itemCounts[i];
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF)); // 최단 거리

    for (int i = 0; i < r; i++) {
        int a, b, l;
        cin >> a >> b >> l;

        dist[a][b] = min(dist[a][b], l);
        dist[b][a] = dist[a][b];
    }

    // 최단 거리 계산
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k || k == i) continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                dist[j][i] = dist[i][j];
            }
        }
    }

    int maxItemCount = 0;

    // 얻을 수 있는 최대 아이템 개수 계산
    for (int i = 1; i <= n; i++) {
        int currItemCount = 0;
        
        // 수색 범위 내의 아이템 수집
        for (int j = 1; j <= n; j++) {
            if (i == j || dist[i][j] <= m) {
                currItemCount += itemCounts[j];
            }
        }

        maxItemCount = max(maxItemCount, currItemCount);
    }

    cout << maxItemCount;
    
    return 0;
}