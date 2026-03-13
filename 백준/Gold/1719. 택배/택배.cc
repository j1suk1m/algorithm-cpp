#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9;
const int NONE = -1;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> firstVisit(n + 1, vector<int>(n + 1, NONE));

    for (int i = 0; i < m; i++) {
        int a, b, time;
        cin >> a >> b >> time;
        
        graph[a][b] = time;
        graph[b][a] = time;

        firstVisit[a][b] = b;
        firstVisit[b][a] = a;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j || j == k || k == i) continue;
                
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    firstVisit[i][j] = firstVisit[i][k];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (firstVisit[i][j] == NONE) {
                cout << "- ";
            } else {
                cout << firstVisit[i][j] << " ";
            }
        }

        cout << "\n";
    }
    
    return 0;
}