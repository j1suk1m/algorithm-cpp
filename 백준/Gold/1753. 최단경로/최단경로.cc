#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int dest;
    int weight;

    Edge(int dest, int weight) {
        this->dest = dest;
        this->weight = weight;
    }
};

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

const int MAX_V = 20000;
const int MAX_W = 10;
const int INF = (MAX_V - 1) * MAX_W + 1;
const string NONE = "INF";

int V, E, K;
vector<vector<Edge>> edges(MAX_V + 1, vector<Edge>()); // 인접 리스트
vector<int> dist(MAX_V + 1, INF); // 정점별 최단 거리

void findMinDistances(int);

int main() {
    cin >> V >> E;
    cin >> K;

    // 인접 리스트 저장
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;

        // 단방향 연결
        edges[src].push_back(Edge(dest, weight));
    }

    // 정점별 최단 거리 계산
    findMinDistances(K);

    // 정점별 최단 거리 출력
    for (int node = 1; node <= V; node++) {
        if (dist[node] < INF) {
            cout << dist[node] << "\n";
        } else {
            cout << NONE << "\n";
        }
    }
    
    return 0;
}

void findMinDistances(int src) {
    priority_queue<State> pq;
    
    dist[src] = 0;
    pq.push(State(src, dist[src]));

    while (!pq.empty()) {
        State curr = pq.top(); pq.pop();

        if (dist[curr.node] < curr.dist) {
            continue;
        }

        for (const Edge& edge : edges[curr.node]) {
            if (dist[edge.dest] > curr.dist + edge.weight) {
                dist[edge.dest] = curr.dist + edge.weight;
                pq.push(State(edge.dest, dist[edge.dest]));
            }
        }
    }
}