#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int v1;
    int v2;
    int cost;

    Edge(int v1, int v2, int cost) {
        this->v1 = v1;
        this->v2 = v2;
        this->cost = cost;
    }
};

const int UPHILL = 0;
const int DOWNHILL = 1;

// 프로토타입
int find(vector<int>& parent, int v);
int calculate(int N, const vector<Edge>& edges);

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;

    for (int i = 0; i < M + 1; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        edges.push_back(Edge(A, B, C));
    }

    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.cost < e2.cost;
    });

    // 오르막길을 최대로 포함하는 최악의 경로의 피로도 계산
    int worst = calculate(N, edges);

    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.cost > e2.cost;
    });
    
    // 오르막길을 최소로 포함하는 최선의 경로의 피로도 계산
    int best = calculate(N, edges);

    cout << worst - best;
    
    return 0;
}

int find(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }

    return parent[v] = find(parent, parent[v]);
}

// 피로도 계산
int calculate(int N, const vector<Edge>& edges) {
    vector<int> parent(N + 1);

    for (int v = 1; v <= N; v++) {
        parent[v] = v;
    }

    int uphillCount = 0;

    for (const auto [v1, v2, cost] : edges) {
        int root1 = find(parent, v1);
        int root2 = find(parent, v2);

        // 사이클 발생 시 간선 skip
        if (root1 == root2) continue;
        
        if (root1 < root2) {
            parent[root2] = root1;
        } else {
            parent[root1] = root2;
        }

        // 오르막길 개수 집계
        if (cost == UPHILL) {
            uphillCount++;
        }
    }

    return uphillCount * uphillCount;
}