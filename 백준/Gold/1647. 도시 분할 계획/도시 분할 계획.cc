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

int find(vector<int>& parent, int v);

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges;

    for (int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        edges.push_back(Edge(A, B, C));
    }

    // 유지비 기준 오름차순 정렬
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
         return e1.cost < e2.cost;
    });

    vector<int> parent(N + 1);

    // 자기 자신 노드로 초기화
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int totalCost = 0;
    int maxCost = 0;

    for (const auto [v1, v2, cost] : edges) {
        int root1 = find(parent, v1);
        int root2 = find(parent, v2);

        if (root1 == root2) { // 사이클이 발생하므로 
            continue; // 이 간선은 최소 신장 트리에 포함하지 않음
        } else if (root1 < root2) {
            parent[root2] = root1;
        } else {
            parent[root1] = root2;
        }

        totalCost += cost;
        maxCost = max(maxCost, cost);
    }

    cout << totalCost - maxCost << "\n";
    
    return 0;
}

int find(vector<int>& parent, int v) {
    if (parent[v] == v) {
        return v;
    }

    return parent[v] = find(parent, parent[v]);
}