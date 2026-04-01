#include <bits/stdc++.h>

using namespace std;

ostringstream oss;

// 프로토타입
bool hasCycle(int curr, int parent, vector<vector<int>>& edges, vector<bool>& visited);
void printResult(int testcase, int treeCount);

int main() {
    // 빠른 입출력 설정
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase = 1;
    int n, m;
    int u, v;
    
    while (cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        
        vector<vector<int>> edges(n + 1, vector<int>());

        // 인접 리스트 정보 저장
        for (int i = 0; i < m; i++) {
            cin >> u >> v;

            // 양방향 연결
            edges[u].push_back(v);
            edges[v].push_back(u);
        }

        int treeCount = 0;
        vector<bool> visited(n + 1, false);

        // 트리 개수 계산
        for (int i = 1; i <= n; i++) {
            // 각 호출마다 연결 요소 하나씩 탐색
            // 사이클이 존재하지 않는 경우 트리 개수 증가
            if (!visited[i] && !hasCycle(i, -1, edges, visited)) { 
                treeCount++;
            }
        }
        
        printResult(testcase, treeCount);
        testcase++;
    }

    cout << oss.str();
    
    return 0;
}

bool hasCycle(int curr, int parent, vector<vector<int>>& edges, vector<bool>& visited) {
    visited[curr] = true;

    for (int next : edges[curr]) {
        if (!visited[next]) {
            if (hasCycle(next, curr, edges, visited)) {
                return true;
            }
        } else if (next != parent) { // 사이클 발견
            return true;
        }
    }

    return false;
}

void printResult(int testcase, int treeCount) {
    oss << "Case " << testcase << ": ";
    
    if (treeCount == 0) {
        oss << "No trees." << "\n";
    } else if (treeCount == 1) {
        oss << "There is one tree." << "\n";
    } else {
        oss << "A forest of " << treeCount << " trees." << "\n";
    }
}