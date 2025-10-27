#include <vector>

using namespace std;

const int MAX = 200;
const int CONNECT = 1;

vector<vector<int>> graph(MAX, vector<int>()); // 인접 리스트
vector<bool> visited(MAX, false); // 방문 여부

void dfs(int curr);

int solution(int n, vector<vector<int>> computers) {    
    // 양방향 연결 관계 저장
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && computers[i][j] == CONNECT) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    int answer = 0;
    
    // 깊이 우선 탐색
    for (int node = 0; node < n; node++) {
        if (!visited[node]) {
            dfs(node); // 해당 node와 동일한 네트워크에 있는 모든 node 방문
            answer++;
        }
    }
    
    return answer;
}

void dfs(int curr) {
    visited[curr] = true;
    
    for (int next : graph[curr]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}