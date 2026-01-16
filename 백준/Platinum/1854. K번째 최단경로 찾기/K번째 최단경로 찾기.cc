#include <bits/stdc++.h>

using namespace std;

// 인접 리스트에서 사용할 구조체
struct Edge {
    int dest;
    int cost;

    Edge(int dest, int cost) {
        this->dest = dest;
        this->cost = cost;
    }
};

// 다익스트라에서 사용할 구조체
struct State {
    int node;
    int dist;

    State(int node, int dist) {
        this->node = node;
        this->dist = dist;
    }

    bool operator<(const State& other) const {
        return dist > other.dist;
    }
};

const int MAX_N = (int)1e3;
const int START = 1;
const int NONE = -1;

int N, M, K;
vector<vector<Edge>> edges(MAX_N + 1, vector<Edge>()); // 인접 리스트
vector<priority_queue<int>> dist(MAX_N + 1, priority_queue<int>()); // 도시별 최단 경로

void dijkstra(int, int);

int main() {
    cin >> N >> M >> K;

    // 인접 리스트 저장
    for (int i = 0; i < M; i++) {
        int src, dest, time;
        cin >> src >> dest >> time;

        // 단방향 연결
        edges[src].push_back(Edge(dest, time));
    }

    // K번째 최단 경로 계산
    dijkstra(START, K);

    for (int node = 1; node <= N; node++) {
        if (dist[node].size() < K) {
            cout << NONE << "\n";
        } else {
            cout << dist[node].top() << "\n";
        }
    }
    
    return 0;
}

void dijkstra(int start, int k) {
    priority_queue<State> pq;

    dist[start].push(0);
    pq.push(State(start, 0));

    while (!pq.empty()) {
        State curr = pq.top(); pq.pop();

        for (const Edge& edge : edges[curr.node]) {
            int nextDist = curr.dist + edge.cost;
            
            if (dist[edge.dest].size() < k) { // k번째 최단 경로가 존재하지 않는 경우
                dist[edge.dest].push(nextDist);
                pq.push(State(edge.dest, nextDist));
            } else if (dist[edge.dest].top() > nextDist) { // 현재 경로가 k번째 최단 경로인 경우
                dist[edge.dest].pop();
                dist[edge.dest].push(nextDist);
                pq.push(State(edge.dest, nextDist));                
            }            
        }
    }
}