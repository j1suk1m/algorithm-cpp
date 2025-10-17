#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) {
        this->to = to;
        this->weight = weight;
    }
};

int N;
const int ROOT = 1;

// 지름의 끝 노드
pair<int, int> dest = make_pair(0, 0); 

// 프로토타입
void dfs(int from, int totalWeights, const vector<vector<Edge>>& edges, vector<bool>& visited);

int main() {
    cin >> N;
    
    vector<vector<Edge>> edges(N + 1); // 인접 리스트
    int parent, child, weight;

    // 인접 리스트 저장
    for (int edge = 0; edge < N - 1; edge++) {
        cin >> parent >> child >> weight;

        edges[parent].push_back(Edge(child, weight));
        edges[child].push_back(Edge(parent, weight));
    }

    // 지름의 한쪽 끝 노드 찾기 (루트에서 출발 -> 가장 먼 노드)
    vector<bool> visited(N + 1, false);
    dfs(ROOT, 0, edges, visited);

    // 지름의 다른 끝 노드 찾기 (지름의 한쪽 끝 노드에서 출발 -> 가장 먼 노드)
    int startNode = dest.first;
    dest = make_pair(0, 0); // dest 초기화
    fill(visited.begin(), visited.end(), false); // visited 초기화
    dfs(startNode, 0, edges, visited);

    // 트리의 지름(지름의 끝 노드를 연결하는 가중치의 합) 출력
    cout << dest.second;
    
    return 0;
}

void dfs(int from, int totalWeights, const vector<vector<Edge>>& edges, vector<bool>& visited) {
    visited[from] = true; // 방문 표시

    // 가장 먼 노드 번호 & 가중치 갱신
    if (totalWeights > dest.second) {
        dest = make_pair(from, totalWeights);
    }

    // 인접 노드 방문
    for (const auto& [to, weight] : edges[from]) {
        if (!visited[to]) {
            dfs(to, totalWeights + weight, edges, visited);
        }
    }
}