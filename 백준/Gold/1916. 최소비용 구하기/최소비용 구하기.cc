#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int node;
    int cost;

    Edge(int node, int cost) {
        this->node = node;
        this->cost = cost;
    }

    bool operator<(const Edge& other) const {
        return cost > other.cost;
    }
};

const int INF = (int)1e8;

int N, M;
vector<vector<Edge>> edges;
vector<int> costs;

int findMinCost(int src, int dest) {
    priority_queue<Edge> PQ;

    costs[src] = 0; 
    PQ.push(Edge(src, costs[src]));

    while (!PQ.empty()) {
        auto [curr, currCost] = PQ.top(); PQ.pop();

        // 이미 최적의 비용이 결정된 경우 무시
        if (costs[curr] < currCost) {
            continue;
        }

        for (const auto& [next, nextCost] : edges[curr]) {
            if (costs[next] > currCost + nextCost) {
                costs[next] = currCost + nextCost;
                PQ.push(Edge(next, costs[next]));
            }
        }                                                                        
    }

    return costs[dest];
}

int main() {
    cin >> N;
    cin >> M;

    edges.assign(N + 1, vector<Edge>());

    // 인접 리스트 저장
    for (int i = 0; i < M; i++) {
        int src, dest, cost;
        cin >> src >> dest >> cost;
        edges[src].push_back(Edge(dest, cost));
    }

    costs.assign(N + 1, INF);

    int src, dest;
    cin >> src >> dest;

    // 최소 비용 계산
    cout << findMinCost(src, dest);
    
    return 0;
}