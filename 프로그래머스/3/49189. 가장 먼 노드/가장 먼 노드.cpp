#include <vector>
#include <queue>

using namespace std;

struct Node {
    int key;
    int dist;
    
    Node(int key, int dist) {
        this->key = key;
        this->dist = dist;
    }
};

const int START = 1; // 시작 노드
vector<int> nodeCount; // nodeCount[distance] = count

int visit(int n, const vector<vector<int>>& graph);

int solution(int n, vector<vector<int>> edges) {
    vector<vector<int>> graph(n + 1, vector<int>()); // 인접 리스트
    
    // 인접 리스트 저장
    for (const vector<int>& edge : edges) {
        int node1 = edge[0];
        int node2 = edge[1];
        
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    
    nodeCount.resize(n);
    
    // 너비 우선 탐색 실행
    int maxDist = visit(n, graph);
    
    // 가장 멀리 떨어진 노드의 개수 반환
    return nodeCount[maxDist];
}

int visit(int n, const vector<vector<int>>& graph) {
    queue<Node> Q;
    vector<bool> visited(n + 1);
    
    Q.push(Node(START, 0));
    visited[START] = true;
    
    int maxDist = 0;
    
    while (!Q.empty()) {
        auto [key, dist] = Q.front(); Q.pop();
        
        // 최대 거리 갱신
        maxDist = dist;
        
        for (int nextKey : graph[key]) {
            if (!visited[nextKey]) {
                int nextDist = dist + 1;
                Q.push(Node(nextKey, nextDist));
                visited[nextKey] = true;
                nodeCount[nextDist]++;
            }
        }
    }
    
    return maxDist;
}